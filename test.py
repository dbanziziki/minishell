import subprocess

class Create_test():
    def __init__(self, cmd):
        self.cmd = cmd
    
    def exec_cmd(self):
        proc = subprocess.Popen(self.cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        proc.communicate()
        stdout, stderr = proc.communicate()
        return (stdout, stderr)

before = Create_test(["make"])
before.exec_cmd()
test = Create_test(["./minishell", "-c", "ls -la"])
stdout, stderr = test.exec_cmd()
after = Create_test(["make", "fclean"])
after.exec_cmd()
print(stdout.decode('utf-8'), end="")
