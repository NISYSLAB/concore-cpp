#PW
import concore
import requests
import time
from ast import literal_eval
import os

#time.sleep(7)
timeout_max=10
concore.delay = 0.02

while not os.path.exists(concore.inpath+'1/ym'):
    time.sleep(concore.delay)

Nsim = 150
init_simtime_u = "[0.0,0.0,0.0,0.0,0.0,0.0,0.0]"
init_simtime_ym = "[0.0,0.0,0.0]"

u = concore.initval(init_simtime_u)
oldu = init_simtime_u
oldt = 0

#initfiles = {'file1': open('./u', 'rb'), 'file2': open('./ym', 'rb')}
initfiles = {'file1': open('./u', 'rb'), 'file2': open(concore.inpath+'1/ym', 'rb')}
# POST Request to /init with u as file1 and ym as file2
r = requests.post('http://www.controlcore.org/init/yuyu', files=initfiles)


while(concore.simtime<Nsim):
    print("PW outer loop")
    while concore.unchanged():
        ym = concore.read(1,"ym",init_simtime_ym)
    f = {'file1': open(concore.inpath+'1/ym', 'rb')}
    print("PW: before post ym="+str(ym))
    r = requests.post('http://www.controlcore.org/ctl/yuyu?fetch=u', files=f,timeout=timeout_max)
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
    print("PW: after post status="+str(r.status_code)+" r.content="+str(r.content)+"/"+r.text)
    #while r.text==oldu or len(r.content)==0:
    while oldt==t or len(r.content)==0:
        time.sleep(concore.delay)
        print("PW waiting status="+str(r.status_code)+" content="+ r.content.decode('utf-8')+" t="+str(t))
        f = {'file1': open(concore.inpath+'1/ym', 'rb')}
        try:
            r = requests.post('http://www.controlcore.org/ctl/yuyu?fetch=u', files=f,timeout=timeout_max)
        except:
            print("PW: bad requests")
        timeout_count += 1
        if r.status_code!=200 or time.perf_counter()-t1 > 1.1*timeout_max: #timeout_count>200:
            print("timeout or bad POST request "+str(r.status_code))
            quit()
        if len(r.text)!=0:
            try:
                t=literal_eval(r.text)[0]
            except:
                print("bad eval "+r.text)
    oldt = t
    oldu = r.text
    print("PW: oldu="+oldu+" t="+str(concore.simtime))
    concore.write(1,"u",oldu)
concore.write(1,"u",init_simtime_u)
print("retry="+str(concore.retrycount))
