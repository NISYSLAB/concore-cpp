global concore;
import_concore;

load("MPC_data.mat");
xm = Data.op1.x0;                         % initial condition of plant
u = Data.op1.us;                          % initial input
disp("us")
disp(u)

concore.retrycount = 0;
concore.delay=0.01;
Nsim=150;
init_simtime_u = "[0,0,0,0,0,0,0]";
init_simtime_ym = "[0,0,0]";
u = concore_initval(init_simtime_u);
ym = concore_initval(init_simtime_ym);

while(concore.simtime<Nsim)
    while concore_unchanged()
        u = concore_read(1,'u',init_simtime_u)';
    end
    %%%%%%%%%%%
    [xm, ym] = Plant(u, xm, Data);
    disp(u)
    disp(ym)
    %%%%%%%%%%%
    concore_write(1,'ym',ym',1);
end
disp("retry=")
disp(concore.retrycount)

