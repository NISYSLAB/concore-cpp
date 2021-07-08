function import_concore
    global concore;

    try
      pid = getpid();
    catch exc
      pid = feature('getpid');
    end
    outputpid = fopen('concorekill.bat','w');
    fprintf(outputpid,'%s',['taskkill /F /PID ',num2str(pid)]);
    fclose(outputpid);

    concore.s = '';
    concore.olds = '';
    concore.delay = 1;
    concore.retrycount = 0;
    if exist('/in1','dir')==7  # 3/20/21  work for docker or local
        concore.inpath = '/in';
        concore.outpath = '/out';
    else
        concore.inpath = 'in';
        concore.outpath = 'out';
    end
    concore.simtime = 0;
end
