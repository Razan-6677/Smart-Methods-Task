L0 = 15;
L1 = 65;
L2 = 100;
L3 = 20;

theta1 = 0;
theta2 = 0;
theta3 = 0;
theta4 = 0;

t1 = deg2rad(theta1);
t2 = deg2rad(theta2);
t3 = deg2rad(theta3);
t4 = deg2rad(theta4);

r  = L1*cos(t2) + L2*cos(t2+t3) + L3*cos(t2+t3+t4);
dy = L1*sin(t2) + L2*sin(t2+t3) + L3*sin(t2+t3+t4);

x = r * cos(t1);
z = r * sin(t1);
y = L0 + dy;

fprintf('x = %.2f mm\n', x);
fprintf('y = %.2f mm\n', y);
fprintf('z = %.2f mm\n', z);
