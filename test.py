import subprocess

make_process = subprocess.Popen(["make"],
                        stdout=subprocess.PIPE,
                        stderr=subprocess.PIPE)

exec_procss = subprocess.Popen(["./minishell", "-c", "kk -la | grep include"],
                        stdout=subprocess.PIPE,
                        stderr=subprocess.PIPE)

stdout, stderr = make_process.communicate();
sout, serr =  exec_procss.communicate();
return_code = exec_procss.poll();
print("return code", return_code);
print(stdout.decode('utf-8'))
print(sout.decode('utf-8'))
print(serr.decode('utf-8'))
