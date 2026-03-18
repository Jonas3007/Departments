#include "Callbacks.h"

#include <string>
#include <vector>

#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Choice.H>

#include "Appcontext.h"
#include "calculator.h"
#include "historyService.h"
#include "UI_HistoryWindow.h"

// ------------------------
// Helper
// ------------------------

static inline std::string get_input(AppContext* ctx) {
	return ctx && ctx->input ? std::string(ctx->input->value()) : std::string{};
}

static inline void set_input(AppContext* ctx, const std::string& s) {
	if (ctx && ctx->input) ctx->input->value(s.c_str());
}

static inline void set_output(AppContext* ctx, const std::string& s) {
	if (ctx && ctx->output) ctx->output->value(s.c_str());
}
static string trimZeros(double result)
{
	string rsString = to_string(result);
	int dotPos = rsString.find('.');
	for(int i = rsString.size()-1; i > dotPos; i-- )
	{
		if(rsString[i] != '0')
		{
			return rsString;
		}
		if(rsString[i] == '0')
		{
			rsString.pop_back();
		}
	}
	if(rsString[rsString.size()-1] == '.')
	{
		rsString.pop_back();
	}
	return rsString;
}

static bool chooseCalculator(const std::string& inputString, AppContext* ctx)
{
	if (!ctx || !ctx->calc || inputString.empty()) return false;

	// 1) Operation an das vorherige Result anhängen: "+5", "-3", "*2", "/4"
	const char c0 = inputString.front();
	if (c0 == '+' || c0 == '-' || c0 == '*' || c0 == '/')
	{
		ctx->calc->PrevResult = ctx->calc->Result;
		ctx->calc->useResultForNextOperation(inputString);
		return true;
	}

	// 2) Mehrere Operatoren / Potenzen / Klammern => gesamter Term
	if (ctx->calc->checkForMultipleOperators(inputString) > 1
		|| inputString.find('^') != std::string::npos
		|| inputString.find('(') != std::string::npos
		|| inputString.find(')') != std::string::npos)
	{
		ctx->calc->calculateTerm(inputString);
		return false;
	}

	// 3) Einfache Operation: split + chooseOperration()
	ctx->calc->splitInput(inputString);
	ctx->calc->chooseOperration(); // (Name wie in deinem Code)
	return false;
}

// ------------------------
// Allgemeine Eingabe-Callbacks
// ------------------------

void append_cb(Fl_Widget* w, void* data)
{
	auto* ctx = static_cast<AppContext*>(data);
	if (!ctx || !ctx->input || !w) return;

	std::string s = get_input(ctx);
	s += w->label();              // Zeichen vom Button anhängen
	set_input(ctx, s);
}

void bracket_cb(Fl_Widget* w, void* data)
{
	auto* ctx = static_cast<AppContext*>(data);
	if (!ctx || !ctx->input) return;

	std::string s = get_input(ctx);
	const auto openPos  = s.find_last_of('(');
	const auto closePos = s.find_last_of(')');

	if (closePos != std::string::npos && closePos > openPos) {
		s += '(';
	} else if (openPos != std::string::npos && openPos > closePos) {
		s += ')';
	} else {
		s += '(';
	}
	set_input(ctx, s);
}

void backspace_cb(Fl_Widget* /*w*/, void* data)
{
	auto* ctx = static_cast<AppContext*>(data);
	if (!ctx || !ctx->input) return;

	std::string s = get_input(ctx);
	if (!s.empty()) {
		s.pop_back();
		set_input(ctx, s);
	}
}

void clear_cb(Fl_Widget* /*w*/, void* data)
{
	auto* ctx = static_cast<AppContext*>(data);
	if (!ctx) return;

	set_input(ctx, "");
	set_output(ctx, "");
}

void calculateResult_cb(Fl_Widget* /*w*/, void* data)
{
	auto* ctx = static_cast<AppContext*>(data);
	if (!ctx || !ctx->calc || !ctx->history) return;

	const std::string inputString = get_input(ctx);
	const bool validInput = ctx->calc->checkForInvalidInput(inputString);

	if (!validInput)
	{
		set_output(ctx, "Invalid");
		ctx->history->AddtoTempHistory(inputString, "Invalid");
		return;
	}

	bool useResult = chooseCalculator(inputString, ctx);

	string rsString = trimZeros(ctx->calc->Result);
	// Historie: Input + Result hinzufügen
	if(useResult == true)
	{
		string prvResStr = trimZeros(ctx->calc->PrevResult);
		ctx->history->AddtoTempHistory(prvResStr + inputString, rsString);
	}
	else
	{
		ctx->history->AddtoTempHistory(inputString, rsString);
	}
	

	// Ausgabe
	
	set_output(ctx, rsString);
}

// ------------------------
// History
// ------------------------

void history_cb(Fl_Widget* /*w*/, void* data)
{
	auto* ctx = static_cast<AppContext*>(data);
	if (!ctx) return;

	(new HistoryWindow(ctx))->show();
}

// QuickSave (QS) im Hauptfenster
void saveHistory_cb(Fl_Widget* w, void* data)
{
	auto* ctx = static_cast<AppContext*>(data);
	if (!ctx || !ctx->history) return;

	// QS speichert einfach in "history"
	ctx->history->setCurrentFile("history");
	ctx->history->SaveHistory();
}

// Nur Platzhalter – wird mit HistoryWindow-Klasse nicht mehr extern gebraucht
void refresh_cb(Fl_Widget* /*w*/, void* /*data*/)
{
	// absichtlich leer
}

// ------------------------
// File-Mode
// ------------------------

void checkBox_cb(Fl_Widget* w, void* data)
{
	auto* ctx = static_cast<AppContext*>(data);
	auto* cb  = dynamic_cast<Fl_Check_Button*>(w);
	if (!ctx || !cb) return;

	const bool enabled = cb->value();
	ctx->fileMode = enabled;

	if (ctx->fileChoice) {
		if (enabled) { ctx->fileChoice->activate(); ctx->fileChoice->show(); }
		else         { ctx->fileChoice->deactivate(); ctx->fileChoice->hide(); }
	}
	if (ctx->addFileButton) {
		if (enabled) { ctx->addFileButton->activate(); ctx->addFileButton->show(); }
		else         { ctx->addFileButton->deactivate(); ctx->addFileButton->hide(); }
	}

	// Wenn File-Mode aus → evtl. eingeblendete Eingabe wieder verstecken
	if (!enabled && ctx->newFileInput) {
		ctx->newFileInput->deactivate();
		ctx->newFileInput->hide();
		ctx->newFileInput->value("");
		ctx->addFilePending = false;
	}
}

void addFile_cb(Fl_Widget* /*w*/, void* data)
{
	auto* ctx = static_cast<AppContext*>(data);
	if (!ctx || !ctx->fileChoice || !ctx->newFileInput || !ctx->history) return;

	if (!ctx->addFilePending)
	{
		// 1. Klick: Eingabefeld zeigen/aktivieren
		ctx->newFileInput->activate();
		ctx->newFileInput->show();
		ctx->addFilePending = true;
		return;
	}

	// 2. Klick: Datei anlegen + Dropdown befüllen
	std::string name = ctx->newFileInput->value();
	if (name.empty()) return;

	// Standard-Endung .txt hinzufügen, falls nicht vorhanden
	if (name.rfind(".txt") != (name.size() >= 4 ? name.size()-4 : std::string::npos)) {
		name += ".txt";
	}

	// In Choice aufnehmen
	ctx->fileChoice->add(name.c_str());

	// Datei erzeugen
	ctx->history->setCurrentFile(name);
	ctx->history->createFile();

	// UI zurücksetzen
	ctx->newFileInput->value("");
	ctx->newFileInput->deactivate();
	ctx->newFileInput->hide();
	ctx->addFilePending = false;
}

void fileChoice_cb(Fl_Widget* w, void* data)
{
	auto* ctx = static_cast<AppContext*>(data);
	auto* choice = dynamic_cast<Fl_Choice*>(w);
	if (!ctx || !choice || !ctx->history || !ctx->calc) return;

	const int idx = choice->value();
	if (idx < 0) return;

	const char* selected = choice->text(idx);
	if (!selected || !*selected) return;

	// Datei auswählen und Berechnungen durchführen
	std::vector<std::string> calculations = ctx->history->GetIncomingFile(selected);
	for (const auto& calcLine : calculations)
	{
		ctx->calc->calculateTerm(calcLine);
		ctx->history->AddtoTempHistory(calcLine, std::to_string(ctx->calc->Result));
	}
	ctx->history->SaveHistory();
}