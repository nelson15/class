e0=[
0, 0, 0, 1
0, 0.166667, 0, 1
0, 0.333333, 0, 1
0, 0.5, 0, 1
0.166667, 0, 0, 1
0.166667, 0.166667, 0, 1
0.166667, 0.333333, 0, 1
0.166667, 0.5, 0, 1
0.333333, 0, 0, 1
0.333333, 0.166667, 0, 1
0.333333, 0.333333, 0, 1
0.333333, 0.5, 0, 1
0.5, 0, 0, 1
0.5, 0.166667, 0, 1
0.5, 0.333333, 0, 1
0.5, 0.5, 0, 1
];

e1=[
0, 0.5, 0, 1
0, 0.666667, 0, 1
0, 0.833333, 0, 1
0, 1, 0, 1
0.166667, 0.5, 0, 1
0.166667, 0.666667, 0, 1
0.166667, 0.833333, 0, 1
0.166667, 1, 0, 1
0.333333, 0.5, 0, 1
0.333333, 0.666667, 0, 1
0.333333, 0.833333, 0, 1
0.333333, 1, 0, 1
0.5, 0.5, 0, 1
0.5, 0.666667, 0, 1
0.5, 0.833333, 0, 1
0.5, 1, 0, 1
];

e2=[
0.5, 0, 0, 1
0.5, 0.166667, 0, 1
0.5, 0.333333, 0, 1
0.5, 0.5, 0, 1
0.666667, 0, 0, 1
0.666667, 0.166667, 0, 1
0.666667, 0.333333, 0, 1
0.666667, 0.5, 0, 1
0.833333, 0, 0, 1
0.833333, 0.166667, 0, 1
0.833333, 0.333333, 0, 1
0.833333, 0.5, 0, 1
1, 0, 0, 1
1, 0.166667, 0, 1
1, 0.333333, 0, 1
1, 0.5, 0, 1
];

e3=[
0.5, 0.5, 0, 1
0.5, 0.666667, 0, 1
0.5, 0.833333, 0, 1
0.5, 1, 0, 1
0.666667, 0.5, 0, 1
0.666667, 0.666667, 0, 1
0.666667, 0.833333, 0, 1
0.666667, 1, 0, 1
0.833333, 0.5, 0, 1
0.833333, 0.666667, 0, 1
0.833333, 0.833333, 0, 1
0.833333, 1, 0, 1
1, 0.5, 0, 1
1, 0.666667, 0, 1
1, 0.833333, 0, 1
1, 1, 0, 1
];

figure;
hold on;
scatter3(e0(:,1),e0(:,2),e0(:,3),200,'.');
scatter3(e1(:,1),e1(:,2),e1(:,3),200,'.');
scatter3(e2(:,1),e2(:,2),e2(:,3),200,'.');
scatter3(e3(:,1),e3(:,2),e3(:,3),200,'.');
