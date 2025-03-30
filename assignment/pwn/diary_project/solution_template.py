### Sample Pwntools script ###
# This script is not optimised, and is just to give you a feel of crafting with pwntools
# More powerful commands are available at https://docs.pwntools.com/
from pwn import *

binary = context.binary = ELF('diaryproject_local')

# If running locally. Comment next line if connecting to server
p = process(binary.path)

# Connect to server. Comment next line if running locally (ie run the previous line)
# p = remote('challenge.cz4067-ctf-trial.site', 3002)


p.recvuntil(b'the day today?\n')
# payload1 = INSERT PAYLOAD
p.sendline(payload1)

# payload2 = INSERT PAYLOAD
p.sendline(payload2)

p.interactive()
