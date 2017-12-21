import bpy
import os

NURBSObject = bpy.context.object.data.splines[0]
p_u = NURBSObject.order_u;
p_v = NURBSObject.order_v;
n_u = NURBSObject.point_count_u
n_v = NURBSObject.point_count_v

cyclic_u = NURBSObject.use_cyclic_u
cyclic_v = NURBSObject.use_cyclic_v
endpnt_u = NURBSObject.use_endpoint_u
endpnt_v = NURBSObject.use_endpoint_v
bezier_u = NURBSObject.use_bezier_u
bezier_v = NURBSObject.use_bezier_v

xs = []
ys = []
zs = []
ws = []

for i in NURBSObject.points:
    xs.append(i.co.x)
    ys.append(i.co.y)
    zs.append(i.co.z)
    ws.append(i.co.w)
os.chdir("/Users/coreynelson/Git/Nelson/ImmersiveSims/ApplicationCode/Shoreline/Geometries/")
exportFile = open("cylinder.nrbpts", "w")

exportFile.write(str(p_u) + ', ' + str(p_v) + '\n')
exportFile.write(str(n_u) + ', ' + str(n_v) + '\n')

exportFile.write(str(cyclic_u) + ', ' + str(cyclic_v) + '\n')
exportFile.write(str(bezier_u) + ', ' + str(bezier_v) + '\n')
exportFile.write(str(endpnt_u) + ', ' + str(endpnt_v) + '\n')


for i in range(0, len(xs)):
    exportFile.write(str(xs[i]) + ', ' + str(ys[i]) + ', '
                    +str(zs[i]) + ', ' + str(ws[i]) + '\n')

exportFile.close()
