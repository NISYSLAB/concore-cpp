#CW
import concore
import requests
import time
from ast import literal_eval
import os

#time.sleep(7)
timeout_max = 20
concore.delay = 0.02

while not os.path.exists(concore.inpath+'1/u'):
    time.sleep(concore.delay)

Nsim = 150
init_simtime_u = "[0.0,0.0,0.0,0.0,0.0,0.0,0.0]"
init_simtime_ym = "[0.0,0.0,0.0]"

ym = concore.initval(init_simtime_ym)
oldym = init_simtime_ym
oldt = 0


while(concore.simtime<Nsim):
    print("CW outer loop")
    while concore.unchanged():
        u = concore.read(1,"u",init_simtime_u)
    f = {'file1': open(concore.inpath+'1/u', 'rb')}
    print("CW: before post u="+str(u))
    r = requests.post('http://www.controlcore.org/pm/yuyu?fetch=ym', files=f,timeout=timeout_max)
    if r.status_code!=200:
        print("bad POST request "+str(r.status_code))
        quit()
    if len(r.text)!=0:
        try:
            t=literal_eval(r.text)[0]
        except:
            print("bad eval "+r.text)
    timeout_count = 0
    t1 = time.perf_counter()
    print("CW: after post status="+str(r.status_code)+" r.content="+str(r.content)+" t="+str(t))
    #while r.text==oldym or len(r.content)==0:
    while oldt==t or len(r.content)==0:
        time.sleep(concore.delay)
        print("CW waiting status="+str(r.status_code)+" content="+ r.content.decode('utf-8')+" t="+str(t))
        f = {'file1': open(concore.inpath+'1/u', 'rb')}
        try:
            r = requests.post('http://www.controlcore.org/pm/yuyu?fetch=ym', files=f,timeout=timeout_max)
        except:
            print("CW: bad request")
        timeout_count += 1
        if r.status_code!=200 or time.perf_counter()-t1 > 1.1*timeout_max: #timeout_count>100:
            print("timeout or bad POST request "+str(r.status_code))
            quit()
        if len(r.text)!=0:
            try:
                t=literal_eval(r.text)[0]
            except:
                print("bad eval "+r.text)
    oldt = t
    oldym = r.text
    print("CW: oldym="+oldym+" t="+str(concore.simtime))
    concore.write(1,"ym",oldym)
concore.write(1,"ym",init_simtime_ym)
print("retry="+str(concore.retrycount))


