import hello
import socket
bs = hello.create(0)
print bs.greet()
wd = hello.create(1)
print wd.greet()
wd.set("hehe")
print wd.greet()

print hello.pt(bs)
print hello.pt(wd)

buf = hello.encode_to_buff()
print type(buf), buf

rbuf = "12345"
hello.decode_from_buff(rbuf)
