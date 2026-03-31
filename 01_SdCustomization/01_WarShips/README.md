# WarShips — v0.1.0-alpha

Ein kleines **Schiffe-versenken-Spiel in C++ mit FLTK-Oberfläche**.
Diese erste Alpha-Version bildet das spielbare Fundament des Projekts: zwei Spieler, Schiffsplatzierung, rundenbasiertes Angreifen und ein einfacher Spielabschluss über die GUI.

## Überblick

**WarShips** ist ein Lern- und Entwicklungsprojekt, das klassische Spielmechanik mit einer einfachen Desktop-Oberfläche verbindet. Der aktuelle Stand **v0.1.0-alpha** richtet sich vor allem an frühe Tests, technische Validierung und die weitere Iteration am Spielfluss.

Der Fokus dieser Version liegt auf:

- einer lauffähigen Grundstruktur des Spiels
- einer FLTK-basierten Benutzeroberfläche
- der Verwaltung von Spielern, Zügen und Schiffen
- der Vorbereitung für weitere Tests und Gameplay-Erweiterungen

## Features in v0.1.0-alpha

- Zwei-Spieler-Ablauf mit Phasensteuerung
- Eingabe und Verwaltung von Spielernamen
- Platzierung von Schiffen auf einem 10x10-Spielfeld
- Prüfung auf gültige Platzierung innerhalb des Spielfelds
- Erkennung von Überschneidungen beim Platzieren
- Rundenbasiertes Angreifen von Koordinaten
- Treffererkennung und Spielfeld-Markierungen
- Einfacher Game-Over-Zustand mit separatem Fenster
- Grundlegende Projektstruktur für Tests mit Catch2

## Technischer Stand

Diese Alpha-Version ist **ein früher Entwicklungsstand**. Das Projekt ist bereits startbar, aber noch nicht vollständig ausgebaut.

Aktuell erkennbar:

- die GUI startet und initialisiert das Spiel
- zentrale Spiellogik liegt in `GameMaster`, `Player` und `Ship`
- FLTK wird als UI-Framework verwendet
- die Teststruktur ist vorhanden, aber noch nicht vollständig ausgebaut
- einzelne Bereiche wirken noch experimentell oder im Umbau

## Projektstruktur

Die wichtigsten Verzeichnisse im Projekt:

- `Context/` – gemeinsame Datentypen und Zustände
- `Models/` – Spiellogik wie Spieler, Schiffe und Spielsteuerung
- `UI/` – Fenster, Oberflächenlogik und Callbacks
- `Helper/` – Hilfsfunktionen für Eingabe und UI
- `Tests/` – erste Unit-Tests mit Catch2
- `Draw.io/` – Entwürfe und Diagramme zum Projekt
