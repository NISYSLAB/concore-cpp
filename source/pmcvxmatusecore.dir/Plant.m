function [newx, newy] = Plant(u, x, Data)
 newx = Data.op1.A * x + Data.op1.B * u;
 newy = Data.op1.C * x + Data.op1.D * u;
end
