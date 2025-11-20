import os
import sys
import argparse

from subprocess import Popen, PIPE
__version__ = "1.0"
statusOK = 0
statusWarn = 1
statusCrit = 2
statusUnk = 3
#cmd = "systemctl status bluetooth.target"


parser = argparse.ArgumentParser(description="Servicename zum checken")

parser.add_argument(
    "-V",
    "--version",
    action="store_true",
    help="print version and exit with UNKNOWN status")

parser.add_argument(
    "-s",
    "--service",
    type = str,
    required = True,
)
parser.add_argument(
    "-w",
    "--warning",
    type = int,
    required = True,
)
parser.add_argument(
    "-c",
    "--critical",
    type = int,
    required= True,
)
parser.add_argument(
    "--memcpu",
    type = str,
    
)

pargs, _ =parser.parse_known_args()
if pargs.version:
    print("Version: "+ __version__)
    sys.exit(statusUnk)
    
cmd= "systemctl status %s" %(pargs.service)
try: 
    p = Popen(cmd, shell=True, stdout=PIPE, stderr=PIPE)
    (output, error) = p.communicate()
    
    output_text = output.decode('utf-8').strip()
    
except OSError as e:
   
    pluginOutput = "Unknown: Etwas hin! Fehler: %s "%(e)
    sys.exit(statusUnk)
pluginOutput =" OK: Hat funktioniert\nOutput: \n%s" %(output_text)
status = ""
memory= ""
data= ''
uptime= ""


for line in output_text.splitlines():
    splittedLine = line.split()
    if splittedLine:
        if splittedLine[0] == "Active:":
            status = splittedLine[1] 
            uptime = ' '.join(splittedLine[8:-1])
        if pargs.memcpu == "mem":
            if splittedLine[0] == "Memory:":
                splittedLine[1] = splittedLine[1][:-1]
                data =float(splittedLine[1])     
        elif pargs.memcpu =="cpu":
            if splittedLine[0] == "CPU":
                splittedLine[1] = splittedLine[1]
                data = float(splittedLine[1])
        else: 
            pluginOutput = "Unknown: --memcpu passt nicht! Fehler: %s "%(pargs.memcpu)
            sys.exit(statusUnk)
                 
if status == "active":
    if data >= pargs.critical:
        pluginOutput = "Warning: Status %s und Memory ist %s" %(status, data)
        pluginStatus = statusCrit
    elif data > pargs.warning:
        pluginOutput = "Warning: Status %s und Memory ist %s" %(status, data)
        pluginStatus = statusWarn
    else:    
        pluginOutput = "Status: %s. Uptime ist: %s" %(status, uptime)  
        pluginStatus = statusOK
else:
    pluginOutput = "Status: %s Uptime: %s" %(status, uptime)  
    pluginStatus = statusCrit

print(pluginOutput)
sys.exit(pluginStatus)

    
    