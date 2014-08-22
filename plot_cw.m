clear all;
[time, cw] = importfile('cw1.log');
[time2, cw2] = importfile('cw11.log');
[time3, cw3] = importfile('cw21.log');
[time4, cw4] = importfile('cw31.log');
[time5, pu] = importfile('PU.log');
plot(time, cw, '-ro');
hold on;
plot(time2 ,cw2, '-bs');
plot(time3, cw3, '-k*');
plot(time4, cw4, '-mx');
stairs(time5, pu*1500, '-g');
legend('TCP over ISM Channel', 'TCP over Licened Channel', ...
    'Simple CR TCP', 'CR TCP', 'PU');
