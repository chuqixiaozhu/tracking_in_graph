import datetime
import subprocess
import sys

# Do experiments many time
time = datetime.datetime.today()
time_fmt = '%Y%m%d-%H%M%S'
path = time.strftime(time_fmt)
# reuilt files are in 'path/'
result_file = path + '-result.txt'
# print('path = {0}'.format(path))
subprocess.call(['mkdir', path], shell=True)
argvs = sys.argv
if len(argvs) <= 1:
    count = 2
else:
    count = int(argvs[1])
for i in range(count):
    for m_num in range(1, 21):
        subprocess.call(['tmp_wait.exe', str(m_num), '100', result_file, '2000'], shell = True)

# Process the results
rf = open(result_file, 'r')
#emt_file = open('d_fov-grid_vs_emt', 'w')
tmd_file = open('m_num-wait_vs_tmd.txt', 'w')
#emt = dict()
tmd = dict()
for line in rf:
    results = line.split()
    var = int(results[0])
    #time = float(results[1])
    dist = float(results[1])
    if var not in tmd.keys():
        #emt[var] = 0.0
        tmd[var] = 0.0
    #emt[var] += time
    tmd[var] += dist
vars = sorted(tmd.keys())
for var in vars:
    #print('{0} {1} {2}'.format(var, emt[var]/count, tmd[var]/count))
    #emt_file.write('{0} {1:.1f}\n'.format(var, emt[var] / count))
    tmd_file.write('{0} {1:.4f}\n'.format(var, tmd[var] / count))
#emt_file.close()
tmd_file.close()
rf.close()
subprocess.call(['move', result_file, path], shell = True)
#subprocess.call(['mv', emt_file.name, path])
subprocess.call(['move', tmd_file.name, path], shell = True)
