function [result] = concore_read(port, name, inistr)
     %declare global variables
     global concore;
     %start of read
     pause(concore.delay);
     try
         % Modified line) 
         input1 = fopen(cat(2,concore.inpath,num2str(port),'/',name));
         concore.s = fscanf(input1,'%c');
         fclose(input1);
     catch exc
         concore.s = inistr;
     end
     while length(concore.s) == 0
         pause(concore.delay);
         % modified fopen
         input1 = fopen(cat(2,concore.inpath,num2str(port),'/',name));
         concore.s = fscanf(input1,'%c');
         fclose(input1);
         concore.retrycount = concore.retrycount + 1;
         %disp("Part 2");
     end
     % changed ym into result var
     result = eval(concore.s);
     concore.simtime = result(1);
     result = result(2:length(result));
     %end of read function
     %disp("Part 3");
end
