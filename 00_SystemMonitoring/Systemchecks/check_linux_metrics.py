#!/usr/bin/env python

# File: check_linux_metrics.py
# URL: https://github.com/kxr/check_linux_metrics
# Author: Khizer Naeem 
# Email: khizernaeem@gmail.com
# Release 0.1: 20/05/2015
# Release 0.2: 02/06/2015
# Release 0.3: 16/07/2015
# 
#
#  Copyright (c) 2015 Khizer Naeem (http://kxr.me)
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#



import sys
import time
import os
import shutil

#Checks if folder exists -> if not create folder "linux_metrics"
INTERIM_DIR = '/var/tmp/linux_metrics'
if not os.path.exists(INTERIM_DIR):
    os.makedirs(INTERIM_DIR)


def check_cpu(warn=70, crit=90):
    status_code = 3
    status_outp = ''
    perfdata = ''

	#if there is no file named "proc_stat" -> create file 
    interim_file = os.path.join(INTERIM_DIR, 'proc_stat')
    if not os.path.isfile(interim_file):
        shutil.copyfile('/proc/stat', interim_file)
        print('First run: please run again to get values')
        sys.exit(0)

	#Logged wann der check durchgeführt worden ist 
    sample_period = float(time.time() - os.path.getmtime(interim_file))
	# reads line 1 and 2 
    with open(interim_file, 'r') as f1:
        line1 = f1.readline()
    with open('/proc/stat', 'r') as f2:
        line2 = f2.readline()
	#splits line 1 and 2 in parts - then subtracts line2 -line1
    deltas = [int(b) - int(a) for a, b in zip(line1.split()[1:], line2.split()[1:])]
    total = sum(deltas)
    percents = [100 - (100 * (float(total - x) / total)) for x in deltas]

    cpu_pcts = {
        'user': percents[0],
        'nice': percents[1],
        'system': percents[2],
        'idle': percents[3],
        'iowait': percents[4],
        'irq': percents[5],
        'softirq': percents[6],
        'steal': percents[7] if len(percents) >= 8 else 0
    }
    cpu_pcts['cpu'] = 100 - cpu_pcts['idle']

    status_outp = f"CPU Usage: {cpu_pcts['cpu']:.2f}% [t:{sample_period:.2f}]"

    if cpu_pcts['cpu'] >= crit:
        status_code = 2
        status_outp += ' (Critical)'
    elif cpu_pcts['cpu'] >= warn:
        status_code = 1
        status_outp += ' (Warning)'
    else:
        status_code = 0
        status_outp += ' (OK)'

    for x in ['cpu', 'user', 'system', 'iowait', 'nice', 'irq', 'softirq', 'steal']:
        perfdata += f"{x}={cpu_pcts[x]:.2f}%;{warn};{crit} \n"

    perfdata = perfdata.strip()
    shutil.copyfile('/proc/stat', interim_file)

    print(f"{status_outp} | {perfdata}\n")
    sys.exit(status_code)

def check_load(warn=[1.0, 2.0, 3.0], crit=[2.0, 4.0, 6.0]):
    status_code = 3
    status_outp = ''
    perfdata = ''

    with open('/proc/loadavg', 'r') as f:
        line = f.readline()
    load_avgs = [float(x) for x in line.split()[:3]]

    load = {
        'load1': load_avgs[0],
        'load5': load_avgs[1],
        'load15': load_avgs[2]
    }

    status_outp = f"Load1: {load['load1']:.2f} Load5: {load['load5']:.2f} Load15: {load['load15']:.2f}"

    status_code = 0
    for i in range(len(load_avgs)):
        if load_avgs[i] >= crit[i]:
            status_code = 2
            status_outp += ' (Critical)'
        elif load_avgs[i] >= warn[i] and status_code < 1:
            status_code = 1
            status_outp += ' (Warning)'
        else:
            status_outp += ' (OK)'

    seq = 0
    for x in ['load1', 'load5', 'load15']:
        perfdata += f"{x}={load[x]:.2f};{warn[seq]};{crit[seq]} "
        seq += 1

    perfdata = perfdata.strip()
    print(f"{status_outp} | {perfdata}\n")
    sys.exit(status_code)

def check_threads(warn=200, crit=400):
    status_code = 3
    status_outp = ''
    perfdata = ''

    with open('/proc/loadavg', 'r') as f:
        line = f.readline()
    t = line.split()[3]
    threads = {
        'running': t.split('/')[0],
        'total': t.split('/')[1]
    }

    status_outp = f"Threads: {t} "

    if float(threads['running']) >= crit:
        status_code = 2
        status_outp += ' (Critical)'
    elif float(threads['running']) >= warn:
        status_code = 1
        status_outp += ' (Warning)'
    else:
        status_code = 0
        status_outp += ' (OK)'

    for x in ['running', 'total']:
        perfdata += f"{x}={float(threads[x]):.2f} "
        if x == 'running':
            perfdata += f";{warn};{crit} "
    perfdata = perfdata.strip()

    print(f"{status_outp} | {perfdata}\n")
    sys.exit(status_code)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("No command given, defaulting to CPU check with warn=70, crit=90\n")
        check_cpu()
    else:
        cmd = sys.argv[1]
        if cmd == "cpu":
            warn = float(sys.argv[2]) if len(sys.argv) > 2 else 70
            crit = float(sys.argv[3]) if len(sys.argv) > 3 else 90
            check_cpu(warn, crit)
        elif cmd == "load":
            warn = [float(x) for x in sys.argv[2:5]] if len(sys.argv) >= 5 else [1.0, 2.0, 3.0]
            crit = [float(x) for x in sys.argv[5:8]] if len(sys.argv) >= 8 else [2.0, 4.0, 6.0]
            check_load(warn, crit)
        elif cmd == "threads":
            warn = float(sys.argv[2]) if len(sys.argv) > 2 else 200
            crit = float(sys.argv[3]) if len(sys.argv) > 3 else 400
            check_threads(warn, crit)
        else:
            print(f"Unknown command: {cmd}\n")
            sys.exit(3)



		
print("Reached end of script")
