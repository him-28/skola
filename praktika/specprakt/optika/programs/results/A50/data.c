void get_r (double l[1500],double y[1500] )
{

//FIXME: loading from file
double rdata[][3] = 
{{190.000000, 0.610269, 1.512637e+01},
{191.000000, 0.617208, 3.617807e+01},
{192.000000, 0.605747, 1.015762e+02},
{193.000000, 0.622291, 2.128607e+02},
{194.000000, 0.609355, 1.850679e+02},
{195.000000, 0.629585, 3.132045e+02},
{196.000000, 0.620400, 4.231856e+02},
{197.000000, 0.643766, 3.294441e+02},
{198.000000, 0.670885, 3.553060e+02},
{199.000000, 0.655281, 1.076392e+03},
{200.000000, 0.657736, 2.282772e+03},
{201.000000, 0.655077, 2.040445e+03},
{202.000000, 0.662237, 1.483832e+03},
{203.000000, 0.668593, 2.639062e+03},
{204.000000, 0.663722, 1.941592e+03},
{205.000000, 0.661865, 2.804914e+03},
{206.000000, 0.662636, 2.479038e+03},
{207.000000, 0.646620, 3.959331e+03},
{208.000000, 0.650185, 4.935148e+03},
{209.000000, 0.653583, 2.461329e+04},
{210.000000, 0.644392, 1.456993e+04},
{211.000000, 0.637623, 1.100629e+04},
{212.000000, 0.636075, 7.388645e+03},
{213.000000, 0.630133, 4.909770e+03},
{214.000000, 0.620627, 1.019970e+04},
{215.000000, 0.612555, 5.215687e+03},
{216.000000, 0.606832, 2.067906e+04},
{217.000000, 0.597806, 2.373829e+04},
{218.000000, 0.591482, 2.089254e+04},
{219.000000, 0.585058, 3.085867e+04},
{220.000000, 0.577533, 3.137442e+04},
{221.000000, 0.564478, 2.238426e+04},
{222.000000, 0.554622, 1.228813e+04},
{223.000000, 0.543668, 1.614472e+04},
{224.000000, 0.533649, 1.484895e+04},
{225.000000, 0.526690, 2.053817e+04},
{226.000000, 0.515683, 3.255689e+04},
{227.000000, 0.501475, 2.650758e+04},
{228.000000, 0.488808, 2.045847e+04},
{229.000000, 0.477953, 2.763859e+04},
{230.000000, 0.464667, 3.235504e+04},
{231.000000, 0.452152, 2.706624e+04},
{232.000000, 0.441007, 2.865577e+04},
{233.000000, 0.430740, 2.647558e+04},
{234.000000, 0.421291, 2.827013e+04},
{235.000000, 0.415307, 3.413261e+04},
{236.000000, 0.408830, 2.840485e+04},
{237.000000, 0.403427, 2.523988e+04},
{238.000000, 0.398698, 2.739866e+04},
{239.000000, 0.395269, 4.046383e+04},
{240.000000, 0.392582, 3.961554e+04},
{241.000000, 0.390856, 3.527271e+04},
{242.000000, 0.391260, 4.348924e+04},
{243.000000, 0.392112, 5.609611e+04},
{244.000000, 0.393600, 8.908823e+04},
{245.000000, 0.395456, 5.762223e+04},
{246.000000, 0.397648, 5.544360e+04},
{247.000000, 0.400794, 8.190698e+04},
{248.000000, 0.403939, 1.085751e+05},
{249.000000, 0.407821, 1.074887e+05},
{250.000000, 0.412379, 1.083362e+05},
{251.000000, 0.416726, 1.313519e+05},
{252.000000, 0.423685, 5.583147e+04},
{253.000000, 0.431272, 7.137323e+04},
{254.000000, 0.437637, 8.227230e+04},
{255.000000, 0.444054, 5.976066e+04},
{256.000000, 0.450891, 5.316924e+04},
{257.000000, 0.458136, 6.982905e+04},
{258.000000, 0.466795, 7.609348e+04},
{259.000000, 0.474699, 4.646233e+04},
{260.000000, 0.484923, 2.874768e+04},
{261.000000, 0.493785, 3.456283e+04},
{262.000000, 0.501203, 4.796569e+04},
{263.000000, 0.508802, 3.061238e+04},
{264.000000, 0.518819, 3.654781e+04},
{265.000000, 0.526992, 3.798353e+04},
{266.000000, 0.535522, 3.358414e+04},
{267.000000, 0.543425, 3.270239e+04},
{268.000000, 0.551192, 3.202190e+04},
{269.000000, 0.558728, 3.369505e+04},
{270.000000, 0.567470, 2.802753e+04},
{271.000000, 0.573625, 2.311002e+04},
{272.000000, 0.578749, 2.584440e+04},
{273.000000, 0.584606, 3.056201e+04},
{274.000000, 0.590853, 3.782258e+04},
{275.000000, 0.594745, 3.000998e+04},
{276.000000, 0.597144, 3.512400e+04},
{277.000000, 0.600491, 3.542858e+04},
{278.000000, 0.604232, 3.678352e+04},
{279.000000, 0.607695, 3.290008e+04},
{280.000000, 0.610086, 2.632687e+04},
{281.000000, 0.612455, 3.139800e+04},
{282.000000, 0.614252, 2.554841e+04},
{283.000000, 0.615451, 2.651826e+04},
{284.000000, 0.615511, 3.623354e+04},
{285.000000, 0.616809, 2.958064e+04},
{286.000000, 0.617159, 3.137907e+04},
{287.000000, 0.617509, 3.431117e+04},
{288.000000, 0.618135, 3.040265e+04},
{289.000000, 0.615751, 3.523853e+04},
{290.000000, 0.612076, 2.831459e+04},
{291.000000, 0.609435, 3.735380e+04},
{292.000000, 0.605148, 3.249251e+04},
{293.000000, 0.601276, 2.483610e+04},
{294.000000, 0.597032, 2.879394e+04},
{295.000000, 0.593090, 2.779684e+04},
{296.000000, 0.589631, 2.790115e+04},
{297.000000, 0.587349, 3.232653e+04},
{298.000000, 0.583753, 2.795448e+04},
{299.000000, 0.581255, 2.945557e+04},
{300.000000, 0.578776, 3.359408e+04},
{301.000000, 0.577246, 2.882135e+04},
{302.000000, 0.575290, 3.310389e+04},
{303.000000, 0.574246, 2.580277e+04},
{304.000000, 0.575134, 3.056176e+04},
{305.000000, 0.572821, 2.753634e+04},
{306.000000, 0.570895, 3.443169e+04},
{307.000000, 0.569688, 5.281616e+04},
{308.000000, 0.569391, 2.682383e+04},
{309.000000, 0.569519, 3.489145e+04},
{310.000000, 0.568268, 3.060183e+04},
{311.000000, 0.567860, 3.272382e+04},
{312.000000, 0.567976, 5.022704e+04},
{313.000000, 0.567223, 3.648811e+04},
{314.000000, 0.566583, 4.690326e+04},
{315.000000, 0.566180, 3.894401e+04},
{316.000000, 0.566216, 2.749941e+04},
{317.000000, 0.565216, 3.719264e+04},
{318.000000, 0.565279, 4.102068e+04},
{319.000000, 0.566132, 3.996646e+04},
{320.000000, 0.566521, 4.487319e+04},
{321.000000, 0.565556, 5.453345e+04},
{322.000000, 0.564779, 3.773532e+04},
{323.000000, 0.565745, 3.853405e+04},
{324.000000, 0.564901, 3.977230e+04},
{325.000000, 0.565600, 3.795708e+04},
{326.000000, 0.567215, 3.408146e+04},
{327.000000, 0.567723, 2.629067e+04},
{328.000000, 0.568023, 1.292313e+04},
{329.000000, 0.568659, 3.687327e+04},
{330.000000, 0.567706, 3.464571e+04},
{331.000000, 0.567504, 2.275039e+04},
{332.000000, 0.566502, 1.642428e+04},
{333.000000, 0.568889, 1.571632e+04},
{334.000000, 0.568570, 1.168192e+04},
{335.000000, 0.565469, 1.406005e+04},
{336.000000, 0.565944, 1.968700e+04},
{337.000000, 0.567006, 2.212942e+04},
{338.000000, 0.565719, 2.839501e+04},
{339.000000, 0.563216, 4.975039e+04},
{340.000000, 0.562911, 2.259417e+04},
{341.000000, 0.564618, 1.764883e+04},
{342.000000, 0.565154, 3.077457e+04},
{343.000000, 0.564318, 2.370719e+04},
{344.000000, 0.564572, 1.779950e+04},
{345.000000, 0.568568, 2.629702e+04},
{346.000000, 0.568455, 5.435325e+04},
{347.000000, 0.568917, 3.049146e+04},
{348.000000, 0.568757, 2.206132e+04},
{349.000000, 0.568262, 2.557725e+04},
{350.000000, 0.569489, 2.613275e+04},
{351.000000, 0.570966, 3.742839e+04},
{352.000000, 0.572318, 1.814155e+04},
{353.000000, 0.575355, 3.313788e+04},
{354.000000, 0.576100, 3.947698e+04},
{355.000000, 0.579360, 3.487862e+04},
{356.000000, 0.579319, 3.177705e+04},
{357.000000, 0.580945, 4.395758e+04},
{358.000000, 0.583345, 4.058605e+04},
{359.000000, 0.586252, 4.957399e+04},
{360.000000, 0.589106, 6.435348e+04},
{361.000000, 0.590888, 5.201543e+04},
{362.000000, 0.591828, 4.752517e+04},
{363.000000, 0.590091, 4.373924e+04},
{364.000000, 0.589968, 5.366281e+04},
{365.000000, 0.590669, 3.402512e+04},
{366.000000, 0.589333, 2.580449e+04},
{367.000000, 0.588036, 2.847689e+04},
{368.000000, 0.586387, 2.714339e+04},
{369.000000, 0.583193, 3.118981e+04},
{370.000000, 0.580337, 4.557902e+04},
{371.000000, 0.576079, 5.369917e+04},
{372.000000, 0.572037, 5.752228e+04},
{373.000000, 0.567087, 4.612595e+04},
{374.000000, 0.562041, 4.077074e+04},
{375.000000, 0.557214, 3.239432e+04},
{376.000000, 0.551375, 2.617764e+04},
{377.000000, 0.547799, 3.177255e+04},
{378.000000, 0.542222, 5.704277e+04},
{379.000000, 0.536708, 3.101661e+04},
{380.000000, 0.534731, 2.969059e+04},
{381.000000, 0.528004, 2.145197e+04},
{382.000000, 0.522508, 7.055477e+04},
{383.000000, 0.518689, 6.360984e+04},
{384.000000, 0.514246, 4.501086e+04},
{385.000000, 0.509062, 4.508803e+04},
{386.000000, 0.503257, 5.837700e+04},
{387.000000, 0.499122, 5.190694e+04},
{388.000000, 0.494896, 7.926265e+04},
{389.000000, 0.491542, 7.722484e+04},
{390.000000, 0.487017, 8.660001e+04},
{391.000000, 0.482158, 8.017876e+04},
{392.000000, 0.477994, 6.365880e+04},
{393.000000, 0.474777, 5.510451e+04},
{394.000000, 0.470334, 6.856482e+04},
{395.000000, 0.466604, 9.056908e+04},
{396.000000, 0.463057, 8.636484e+04},
{397.000000, 0.458575, 6.907196e+04},
{398.000000, 0.455062, 5.351082e+04},
{399.000000, 0.451451, 7.149057e+04},
{400.000000, 0.448756, 7.922024e+04},
{401.000000, 0.444966, 1.122627e+05},
{402.000000, 0.441159, 9.552187e+04},
{403.000000, 0.436630, 7.569604e+04},
{404.000000, 0.433877, 6.730756e+04},
{405.000000, 0.430905, 6.935649e+04},
{406.000000, 0.426945, 9.658828e+04},
{407.000000, 0.423809, 1.055833e+05},
{408.000000, 0.420312, 7.811880e+04},
{409.000000, 0.416538, 9.183213e+04},
{410.000000, 0.413103, 8.008340e+04},
{411.000000, 0.410361, 8.568150e+04},
{412.000000, 0.407233, 8.093067e+04},
{413.000000, 0.404297, 9.123276e+04},
{414.000000, 0.401290, 1.051540e+05},
{415.000000, 0.398574, 1.304304e+05},
{416.000000, 0.395848, 1.225542e+05},
{417.000000, 0.392678, 9.284251e+04},
{418.000000, 0.389112, 1.176871e+05},
{419.000000, 0.386286, 1.421247e+05},
{420.000000, 0.382797, 1.314512e+05},
{421.000000, 0.380137, 1.196166e+05},
{422.000000, 0.377532, 1.069158e+05},
{423.000000, 0.374126, 9.085292e+04},
{424.000000, 0.371509, 1.072030e+05},
{425.000000, 0.368557, 9.385661e+04},
{426.000000, 0.365754, 1.050324e+05},
{427.000000, 0.362784, 1.011339e+05},
{428.000000, 0.360249, 1.294470e+05},
{429.000000, 0.357833, 9.866959e+04},
{430.000000, 0.354537, 9.602973e+04},
{431.000000, 0.351900, 1.034376e+05},
{432.000000, 0.349058, 1.027058e+05},
{433.000000, 0.346735, 8.672964e+04},
{434.000000, 0.344367, 1.163200e+05},
{435.000000, 0.341416, 1.173975e+05},
{436.000000, 0.338499, 1.009291e+05},
{437.000000, 0.335944, 1.067978e+05},
{438.000000, 0.333342, 9.785202e+04},
{439.000000, 0.330446, 9.359673e+04},
{440.000000, 0.328153, 9.568606e+04},
{441.000000, 0.325956, 1.318535e+05},
{442.000000, 0.323297, 1.303991e+05},
{443.000000, 0.320654, 1.331014e+05},
{444.000000, 0.317585, 1.391214e+05},
{445.000000, 0.315601, 9.598445e+04},
{446.000000, 0.312873, 1.058195e+05},
{447.000000, 0.310286, 1.145704e+05},
{448.000000, 0.308347, 1.272532e+05},
{449.000000, 0.305938, 1.246945e+05},
{450.000000, 0.303339, 1.127827e+05},
{451.000000, 0.301056, 1.310889e+05},
{452.000000, 0.298815, 1.370652e+05},
{453.000000, 0.296241, 1.266983e+05},
{454.000000, 0.293662, 1.190371e+05},
{455.000000, 0.291606, 1.126052e+05},
{456.000000, 0.289276, 1.170565e+05},
{457.000000, 0.287311, 1.221156e+05},
{458.000000, 0.285161, 1.141526e+05},
{459.000000, 0.282932, 1.148098e+05},
{460.000000, 0.280632, 1.189961e+05},
{461.000000, 0.278326, 1.248839e+05},
{462.000000, 0.275933, 1.275299e+05},
{463.000000, 0.273754, 1.197983e+05},
{464.000000, 0.271637, 1.070594e+05},
{465.000000, 0.269445, 1.034862e+05},
{466.000000, 0.267617, 1.036615e+05},
{467.000000, 0.265655, 1.094869e+05},
{468.000000, 0.263445, 9.395482e+04},
{469.000000, 0.261388, 1.017109e+05},
{470.000000, 0.259321, 1.004365e+05},
{471.000000, 0.256788, 9.422178e+04},
{472.000000, 0.254619, 9.081045e+04},
{473.000000, 0.252479, 1.078785e+05},
{474.000000, 0.250798, 1.020940e+05},
{475.000000, 0.249260, 9.716309e+04},
{476.000000, 0.247348, 9.160268e+04},
{477.000000, 0.245327, 9.845049e+04},
{478.000000, 0.243382, 8.938779e+04},
{479.000000, 0.241129, 9.084080e+04},
{480.000000, 0.239147, 9.133024e+04},
{481.000000, 0.237236, 8.665428e+04},
{482.000000, 0.235522, 8.343757e+04},
{483.000000, 0.234035, 8.737207e+04},
{484.000000, 0.231917, 9.229345e+04},
{485.000000, 0.230183, 8.982743e+04},
{486.000000, 0.228473, 9.702868e+04},
{487.000000, 0.226563, 1.044761e+05},
{488.000000, 0.224666, 8.985578e+04},
{489.000000, 0.222765, 9.117835e+04},
{490.000000, 0.221224, 9.001106e+04},
{491.000000, 0.219601, 8.244297e+04},
{492.000000, 0.217797, 8.061635e+04},
{493.000000, 0.216078, 9.685960e+04},
{494.000000, 0.214278, 9.910493e+04},
{495.000000, 0.212637, 9.128607e+04},
{496.000000, 0.210904, 9.503926e+04},
{497.000000, 0.209091, 9.730299e+04},
{498.000000, 0.207353, 1.022382e+05},
{499.000000, 0.205663, 9.769492e+04},
{500.000000, 0.204031, 9.484786e+04},
{501.000000, 0.202602, 9.403049e+04},
{502.000000, 0.201139, 8.962885e+04},
{503.000000, 0.199585, 8.652182e+04},
{504.000000, 0.198079, 8.652336e+04},
{505.000000, 0.196430, 8.420633e+04},
{506.000000, 0.194895, 8.311134e+04},
{507.000000, 0.193347, 8.674145e+04},
{508.000000, 0.191699, 8.673128e+04},
{509.000000, 0.190371, 8.741383e+04},
{510.000000, 0.189062, 8.592044e+04},
{511.000000, 0.187488, 8.088354e+04},
{512.000000, 0.186082, 7.985974e+04},
{513.000000, 0.184637, 8.295692e+04},
{514.000000, 0.183047, 7.751188e+04},
{515.000000, 0.181611, 8.134795e+04},
{516.000000, 0.180224, 8.722628e+04},
{517.000000, 0.178963, 8.101815e+04},
{518.000000, 0.177675, 8.574503e+04},
{519.000000, 0.176333, 8.864145e+04},
{520.000000, 0.174931, 8.423476e+04},
{521.000000, 0.173680, 8.664890e+04},
{522.000000, 0.172260, 7.925567e+04},
{523.000000, 0.170830, 7.509483e+04},
{524.000000, 0.169613, 8.072559e+04},
{525.000000, 0.168355, 7.889680e+04},
{526.000000, 0.167041, 7.845146e+04},
{527.000000, 0.165894, 8.098998e+04},
{528.000000, 0.164618, 8.915547e+04},
{529.000000, 0.163309, 8.443255e+04},
{530.000000, 0.162167, 8.354110e+04},
{531.000000, 0.160832, 8.231414e+04},
{532.000000, 0.159527, 8.414757e+04},
{533.000000, 0.158359, 8.733559e+04},
{534.000000, 0.157187, 8.722687e+04},
{535.000000, 0.156103, 8.546456e+04},
{536.000000, 0.155144, 8.358973e+04},
{537.000000, 0.153998, 8.856091e+04},
{538.000000, 0.152976, 8.345233e+04},
{539.000000, 0.151791, 8.586171e+04},
{540.000000, 0.150587, 8.868409e+04},
{541.000000, 0.149475, 8.430845e+04},
{542.000000, 0.148466, 8.414717e+04},
{543.000000, 0.147422, 8.451212e+04},
{544.000000, 0.146401, 8.046712e+04},
{545.000000, 0.145420, 8.215913e+04},
{546.000000, 0.144514, 8.434787e+04},
{547.000000, 0.143567, 8.662853e+04},
{548.000000, 0.142570, 8.739239e+04},
{549.000000, 0.141521, 8.999360e+04},
{550.000000, 0.140508, 9.287371e+04},
{551.000000, 0.139532, 8.916812e+04},
{552.000000, 0.138581, 8.662788e+04},
{553.000000, 0.137741, 8.809220e+04},
{554.000000, 0.136807, 8.766757e+04},
{555.000000, 0.135812, 9.384674e+04},
{556.000000, 0.134926, 9.281015e+04},
{557.000000, 0.133934, 9.377887e+04},
{558.000000, 0.132947, 9.414635e+04},
{559.000000, 0.131995, 9.414881e+04},
{560.000000, 0.131259, 9.408268e+04},
{561.000000, 0.130335, 9.344920e+04},
{562.000000, 0.129552, 9.411851e+04},
{563.000000, 0.128781, 9.854926e+04},
{564.000000, 0.128003, 9.963739e+04},
{565.000000, 0.127272, 9.589790e+04},
{566.000000, 0.126294, 1.028855e+05},
{567.000000, 0.125546, 9.562128e+04},
{568.000000, 0.124889, 8.710012e+04},
{569.000000, 0.124097, 9.555863e+04},
{570.000000, 0.123385, 9.499639e+04},
{571.000000, 0.122711, 1.007300e+05},
{572.000000, 0.121919, 1.006337e+05},
{573.000000, 0.121308, 9.563499e+04},
{574.000000, 0.120549, 1.002192e+05},
{575.000000, 0.119622, 1.023529e+05},
{576.000000, 0.119003, 9.951252e+04},
{577.000000, 0.118281, 9.616556e+04},
{578.000000, 0.117648, 9.399522e+04},
{579.000000, 0.117069, 9.835412e+04},
{580.000000, 0.116384, 1.022694e+05},
{581.000000, 0.115831, 1.006321e+05},
{582.000000, 0.115169, 9.732977e+04},
{583.000000, 0.114436, 9.767400e+04},
{584.000000, 0.113819, 9.604923e+04},
{585.000000, 0.113252, 9.792494e+04},
{586.000000, 0.112633, 9.881597e+04},
{587.000000, 0.112107, 9.998481e+04},
{588.000000, 0.111624, 1.045519e+05},
{589.000000, 0.111037, 1.029972e+05},
{590.000000, 0.110468, 9.813201e+04},
{591.000000, 0.109891, 9.687244e+04},
{592.000000, 0.109173, 9.175718e+04},
{593.000000, 0.108639, 9.315598e+04},
{594.000000, 0.108124, 9.867759e+04},
{595.000000, 0.107573, 9.955941e+04},
{596.000000, 0.107215, 9.777950e+04},
{597.000000, 0.106930, 1.012733e+05},
{598.000000, 0.106409, 1.077311e+05},
{599.000000, 0.105901, 9.961626e+04},
{600.000000, 0.105392, 9.758258e+04},
{601.000000, 0.104834, 1.118850e+05},
{602.000000, 0.104344, 1.072480e+05},
{603.000000, 0.103886, 1.054662e+05},
{604.000000, 0.103438, 1.100725e+05},
{605.000000, 0.103259, 1.131087e+05},
{606.000000, 0.102892, 1.096559e+05},
{607.000000, 0.102316, 1.091142e+05},
{608.000000, 0.102048, 1.144532e+05},
{609.000000, 0.101329, 1.133730e+05},
{610.000000, 0.100818, 1.031943e+05},
{611.000000, 0.100425, 1.179607e+05},
{612.000000, 0.100161, 1.090013e+05},
{613.000000, 0.099798, 1.179591e+05},
{614.000000, 0.099612, 1.138971e+05},
{615.000000, 0.099392, 1.276405e+05},
{616.000000, 0.098980, 1.159793e+05},
{617.000000, 0.098526, 1.145977e+05},
{618.000000, 0.098022, 1.120566e+05},
{619.000000, 0.097626, 1.143543e+05},
{620.000000, 0.097310, 1.291821e+05},
{621.000000, 0.097144, 1.217931e+05},
{622.000000, 0.096863, 1.200180e+05},
{623.000000, 0.096649, 1.212376e+05},
{624.000000, 0.096506, 1.242273e+05},
{625.000000, 0.096160, 1.231889e+05},
{626.000000, 0.095803, 1.145852e+05},
{627.000000, 0.095389, 1.148107e+05},
{628.000000, 0.095006, 1.206867e+05},
{629.000000, 0.094846, 1.163963e+05},
{630.000000, 0.094521, 1.141673e+05},
{631.000000, 0.094340, 1.128739e+05},
{632.000000, 0.094246, 1.226787e+05},
{633.000000, 0.094095, 1.255951e+05},
{634.000000, 0.093825, 1.272371e+05},
{635.000000, 0.093621, 1.264182e+05},
{636.000000, 0.093223, 1.284046e+05},
{637.000000, 0.092827, 1.255219e+05},
{638.000000, 0.092693, 1.222699e+05},
{639.000000, 0.092562, 1.284620e+05},
{640.000000, 0.092642, 1.283222e+05},
{641.000000, 0.092546, 1.288542e+05},
{642.000000, 0.092274, 1.262516e+05},
{643.000000, 0.092082, 1.273646e+05},
{644.000000, 0.091799, 1.322162e+05},
{645.000000, 0.091404, 1.394804e+05},
{646.000000, 0.091321, 1.447838e+05},
{647.000000, 0.091228, 1.363808e+05},
{648.000000, 0.091249, 1.225006e+05},
{649.000000, 0.091189, 1.310133e+05},
{650.000000, 0.090922, 1.338322e+05},
{651.000000, 0.090832, 1.568448e+05},
{652.000000, 0.090695, 1.391795e+05},
{653.000000, 0.090220, 1.410599e+05},
{654.000000, 0.090051, 1.556393e+05},
{655.000000, 0.089979, 1.493898e+05},
{656.000000, 0.089716, 1.293269e+05},
{657.000000, 0.090077, 1.328335e+05},
{658.000000, 0.090265, 1.237306e+05},
{659.000000, 0.090265, 1.351463e+05},
{660.000000, 0.090210, 1.286174e+05},
{661.000000, 0.089660, 1.355792e+05},
{662.000000, 0.089452, 1.429231e+05},
{663.000000, 0.089380, 1.661615e+05},
{664.000000, 0.089248, 1.489829e+05},
{665.000000, 0.089272, 1.409136e+05},
{666.000000, 0.089352, 1.432586e+05},
{667.000000, 0.089343, 1.266009e+05},
{668.000000, 0.089324, 1.361018e+05},
{669.000000, 0.089557, 1.336595e+05},
{670.000000, 0.089452, 1.594587e+05},
{671.000000, 0.089283, 1.644086e+05},
{672.000000, 0.089200, 1.546220e+05},
{673.000000, 0.089147, 1.408047e+05},
{674.000000, 0.089127, 1.449611e+05},
{675.000000, 0.088937, 1.522685e+05},
{676.000000, 0.088772, 1.704828e+05},
{677.000000, 0.088754, 1.579774e+05},
{678.000000, 0.088780, 1.588216e+05},
{679.000000, 0.088869, 1.741720e+05},
{680.000000, 0.088960, 1.855699e+05},
{681.000000, 0.088932, 1.827575e+05},
{682.000000, 0.088975, 1.787534e+05},
{683.000000, 0.088841, 1.777269e+05},
{684.000000, 0.088696, 1.810038e+05},
{685.000000, 0.088828, 1.721636e+05},
{686.000000, 0.088903, 1.725875e+05},
{687.000000, 0.088963, 1.806849e+05},
{688.000000, 0.089105, 1.543587e+05},
{689.000000, 0.089234, 1.497942e+05},
{690.000000, 0.089337, 1.765506e+05},
{691.000000, 0.089312, 1.844734e+05},
{692.000000, 0.089220, 1.846784e+05},
{693.000000, 0.089053, 1.791392e+05},
{694.000000, 0.088959, 1.847731e+05},
{695.000000, 0.089048, 1.871779e+05},
{696.000000, 0.089403, 1.974999e+05},
{697.000000, 0.089508, 2.092545e+05},
{698.000000, 0.089662, 1.940563e+05},
{699.000000, 0.089605, 1.978637e+05},
{700.000000, 0.089721, 2.114404e+05},
{701.000000, 0.089431, 1.900930e+05},
{702.000000, 0.089779, 1.719021e+05},
{703.000000, 0.089782, 1.662860e+05},
{704.000000, 0.089700, 1.866705e+05},
{705.000000, 0.089986, 1.861507e+05},
{706.000000, 0.090236, 1.978316e+05},
{707.000000, 0.090519, 2.108378e+05},
{708.000000, 0.090517, 1.850627e+05},
{709.000000, 0.090348, 2.164494e+05},
{710.000000, 0.090282, 2.219953e+05},
{711.000000, 0.090329, 2.161771e+05},
{712.000000, 0.090574, 2.022997e+05},
{713.000000, 0.090690, 2.154710e+05},
{714.000000, 0.090913, 2.357521e+05},
{715.000000, 0.091106, 2.209043e+05},
{716.000000, 0.091227, 2.172637e+05},
{717.000000, 0.091238, 2.249669e+05},
{718.000000, 0.091300, 2.165584e+05},
{719.000000, 0.091385, 2.288758e+05},
{720.000000, 0.091450, 2.115993e+05},
{721.000000, 0.091467, 2.001042e+05},
{722.000000, 0.091618, 2.072627e+05},
{723.000000, 0.091873, 2.101372e+05},
{724.000000, 0.092128, 2.066288e+05},
{725.000000, 0.092270, 1.910169e+05},
{726.000000, 0.092304, 2.129475e+05},
{727.000000, 0.092242, 2.139411e+05},
{728.000000, 0.092148, 2.128309e+05},
{729.000000, 0.092371, 2.211314e+05},
{730.000000, 0.092512, 2.313714e+05},
{731.000000, 0.092665, 2.417564e+05},
{732.000000, 0.092986, 2.344615e+05},
{733.000000, 0.093264, 2.284842e+05},
{734.000000, 0.093500, 2.136333e+05},
{735.000000, 0.093584, 2.125774e+05},
{736.000000, 0.093494, 2.074967e+05},
{737.000000, 0.093621, 2.294594e+05},
{738.000000, 0.093758, 2.560379e+05},
{739.000000, 0.093910, 2.218109e+05},
{740.000000, 0.094465, 2.200371e+05},
{741.000000, 0.094685, 2.127221e+05},
{742.000000, 0.094726, 2.040883e+05},
{743.000000, 0.095000, 2.441781e+05},
{744.000000, 0.094924, 2.465328e+05},
{745.000000, 0.094851, 2.118292e+05},
{746.000000, 0.095015, 2.422252e+05},
{747.000000, 0.095198, 2.371443e+05},
{748.000000, 0.095185, 2.273716e+05},
{749.000000, 0.095731, 2.446764e+05},
{750.000000, 0.095978, 2.950702e+05},
{751.000000, 0.096185, 2.952979e+05},
{752.000000, 0.096460, 2.701229e+05},
{753.000000, 0.096550, 2.725340e+05},
{754.000000, 0.096559, 2.706972e+05},
{755.000000, 0.096610, 2.478178e+05},
{756.000000, 0.096618, 2.263392e+05},
{757.000000, 0.096970, 2.725568e+05},
{758.000000, 0.097389, 2.414890e+05},
{759.000000, 0.097637, 2.889181e+05},
{760.000000, 0.097914, 3.182175e+05},
{761.000000, 0.098025, 2.716894e+05},
{762.000000, 0.097969, 3.050081e+05},
{763.000000, 0.098049, 2.905605e+05},
{764.000000, 0.098190, 2.704305e+05},
{765.000000, 0.098409, 2.790777e+05},
{766.000000, 0.098767, 2.765450e+05},
{767.000000, 0.099121, 3.480807e+05},
{768.000000, 0.099452, 4.158241e+05},
{769.000000, 0.099757, 2.875449e+05},
{770.000000, 0.099860, 2.903353e+05},
{771.000000, 0.099952, 3.297819e+05},
{772.000000, 0.100017, 3.245578e+05},
{773.000000, 0.100160, 3.267036e+05},
{774.000000, 0.100480, 2.931835e+05},
{775.000000, 0.101012, 3.175022e+05},
{776.000000, 0.101249, 3.364416e+05},
{777.000000, 0.101408, 3.108265e+05},
{778.000000, 0.101533, 2.026609e+05},
{779.000000, 0.101800, 2.303652e+05},
{780.000000, 0.101827, 4.250747e+05},
{781.000000, 0.101843, 2.471989e+05},
{782.000000, 0.102041, 2.217663e+05},
{783.000000, 0.102509, 2.670102e+05},
{784.000000, 0.102778, 3.741565e+05},
{785.000000, 0.103386, 2.167104e+05},
{786.000000, 0.103323, 3.230933e+05},
{787.000000, 0.103575, 2.810419e+05},
{788.000000, 0.103547, 3.093929e+05},
{789.000000, 0.103546, 2.682452e+05},
{790.000000, 0.103604, 2.639995e+05},
{791.000000, 0.103984, 3.293150e+05},
{792.000000, 0.104611, 3.198944e+05},
{793.000000, 0.105356, 4.340993e+05},
{794.000000, 0.105570, 5.477172e+05},
{795.000000, 0.105627, 3.856356e+05},
{796.000000, 0.105743, 2.619441e+05},
{797.000000, 0.105641, 4.056464e+05},
{798.000000, 0.105795, 4.094621e+05},
{799.000000, 0.105724, 3.322520e+05},
{800.000000, 0.105660, 3.720665e+05},
{801.000000, 0.106432, 4.299597e+05},
{802.000000, 0.106877, 4.020056e+05},
{803.000000, 0.106896, 3.536385e+05},
{804.000000, 0.107449, 3.240875e+05},
{805.000000, 0.107576, 2.644419e+05},
{806.000000, 0.107625, 2.881442e+05},
{807.000000, 0.107706, 3.784724e+05},
{808.000000, 0.108035, 4.158949e+05},
{809.000000, 0.108413, 4.896576e+05},
{810.000000, 0.108651, 3.747492e+05},
{811.000000, 0.109268, 4.036636e+05},
{812.000000, 0.109541, 3.360382e+05},
{813.000000, 0.109454, 3.428005e+05},
{814.000000, 0.109597, 3.904017e+05},
{815.000000, 0.109396, 3.784032e+05},
{816.000000, 0.109845, 3.402853e+05},
{817.000000, 0.109881, 4.550617e+05},
{818.000000, 0.110226, 3.363955e+05},
{819.000000, 0.111240, 3.699786e+05},
{820.000000, 0.111699, 3.535142e+05},
{821.000000, 0.111441, 4.342864e+05},
{822.000000, 0.111919, 2.616127e+05},
{823.000000, 0.111475, 3.569509e+05},
{824.000000, 0.111435, 4.375254e+05},
{825.000000, 0.112020, 2.654170e+05},
{826.000000, 0.112598, 2.862441e+05},
{827.000000, 0.113129, 3.497739e+05},
{828.000000, 0.113478, 3.666867e+05},
{829.000000, 0.113451, 5.489761e+05},
{830.000000, 0.113557, 3.656100e+05},
{831.000000, 0.113706, 2.906218e+05},
{832.000000, 0.113394, 3.178045e+05},
{833.000000, 0.114174, 2.777469e+05},
{834.000000, 0.114016, 5.802416e+05},
{835.000000, 0.114878, 4.387797e+05},
{836.000000, 0.115100, 5.317052e+05},
{837.000000, 0.115619, 3.905619e+05},
{838.000000, 0.115972, 2.955763e+05},
{839.000000, 0.116211, 3.605593e+05},
{840.000000, 0.115940, 3.909425e+05},
{841.000000, 0.116397, 3.293929e+05},
{842.000000, 0.116281, 2.893302e+05},
{843.000000, 0.115987, 4.184753e+05},
{844.000000, 0.117044, 3.710806e+05},
{845.000000, 0.117993, 3.386409e+05},
{846.000000, 0.118095, 4.733936e+05},
{847.000000, 0.118238, 5.027405e+05},
{848.000000, 0.118506, 4.879540e+05},
{849.000000, 0.117958, 4.277355e+05},
{850.000000, 0.118199, 5.218439e+05},
{851.000000, 0.118690, 5.822290e+05},
{852.000000, 0.118513, 4.842140e+05},
{853.000000, 0.119008, 4.005714e+05},
{854.000000, 0.119696, 5.564716e+05},
{855.000000, 0.120376, 3.922490e+05},
{856.000000, 0.120637, 2.248747e+05},
{857.000000, 0.120826, 4.039611e+05},
{858.000000, 0.120495, 5.732632e+05},
{859.000000, 0.120491, 1.110591e+06},
{860.000000, 0.120737, 4.668043e+05},
{861.000000, 0.120848, 3.372569e+05},
{862.000000, 0.121615, 2.474447e+05},
{863.000000, 0.121943, 5.090612e+05},
{864.000000, 0.122796, 3.004881e+05},
{865.000000, 0.123242, 4.427010e+05},
{866.000000, 0.123374, 3.252453e+05},
{867.000000, 0.122822, 2.118469e+05},
{868.000000, 0.122487, 4.238340e+05},
{869.000000, 0.122924, 3.151640e+05},
{870.000000, 0.123413, 3.968047e+05},
{871.000000, 0.124472, 7.219403e+05},
{872.000000, 0.124591, 3.413313e+05},
{873.000000, 0.125020, 5.667066e+05},
{874.000000, 0.124582, 3.896654e+05},
{875.000000, 0.124734, 2.304138e+05},
{876.000000, 0.124835, 2.647796e+05},
{877.000000, 0.124898, 3.260921e+05},
{878.000000, 0.125272, 3.058876e+05},
{879.000000, 0.125798, 3.290837e+05},
{880.000000, 0.127268, 2.271488e+05},
{881.000000, 0.126626, 3.165550e+05},
{882.000000, 0.127004, 6.463817e+05},
{883.000000, 0.127647, 3.464677e+05},
{884.000000, 0.126670, 4.292540e+05},
{885.000000, 0.127312, 4.184742e+05},
{886.000000, 0.127422, 4.286288e+05},
{887.000000, 0.127935, 3.559717e+05},
{888.000000, 0.128640, 3.850037e+05},
{889.000000, 0.128684, 5.009231e+05},
{890.000000, 0.128802, 5.255064e+05},
{891.000000, 0.128862, 4.793695e+05},
{892.000000, 0.129077, 4.948926e+05},
{893.000000, 0.128939, 4.462637e+05},
{894.000000, 0.129116, 4.000067e+05},
{895.000000, 0.129172, 5.078723e+05},
{896.000000, 0.129380, 5.429925e+05},
{897.000000, 0.130429, 4.640211e+05},
{898.000000, 0.130887, 5.284976e+05},
{899.000000, 0.131383, 7.134544e+05},
{900.000000, 0.131748, 4.889612e+05},
{901.000000, 0.131835, 4.610917e+05},
{902.000000, 0.131827, 4.727930e+05},
{903.000000, 0.132017, 5.136941e+05},
{904.000000, 0.131416, 7.720587e+05},
{905.000000, 0.131856, 6.973848e+05},
{906.000000, 0.132154, 6.159554e+05},
{907.000000, 0.132369, 3.452172e+05},
{908.000000, 0.132934, 3.601625e+05},
{909.000000, 0.132928, 3.599899e+05},
{910.000000, 0.133746, 7.889662e+05},
{911.000000, 0.134413, 4.068139e+05},
{912.000000, 0.133812, 4.448189e+05},
{913.000000, 0.134077, 5.738823e+05},
{914.000000, 0.134280, 5.405232e+05},
{915.000000, 0.134800, 4.586380e+05},
{916.000000, 0.135051, 4.419888e+05},
{917.000000, 0.135390, 6.771032e+05},
{918.000000, 0.135811, 6.688865e+05},
{919.000000, 0.136009, 5.248038e+05},
{920.000000, 0.136040, 5.523132e+05},
{921.000000, 0.135973, 5.264510e+05},
{922.000000, 0.136449, 4.622672e+05},
{923.000000, 0.136632, 4.455338e+05},
{924.000000, 0.137069, 6.239329e+05},
{925.000000, 0.137489, 4.072947e+05},
{926.000000, 0.137531, 4.628177e+05},
{927.000000, 0.137768, 5.461344e+05},
{928.000000, 0.137990, 5.231644e+05},
{929.000000, 0.138015, 5.505208e+05},
{930.000000, 0.138145, 4.831926e+05},
{931.000000, 0.138461, 4.266327e+05},
{932.000000, 0.138982, 4.142293e+05},
{933.000000, 0.139293, 5.523558e+05},
{934.000000, 0.139645, 5.841262e+05},
{935.000000, 0.139985, 6.042808e+05},
{936.000000, 0.140025, 4.844555e+05},
{937.000000, 0.139969, 6.667292e+05},
{938.000000, 0.140352, 7.877468e+05},
{939.000000, 0.140649, 1.078797e+06},
{940.000000, 0.140689, 6.673811e+05},
{941.000000, 0.141201, 4.590063e+05},
{942.000000, 0.141535, 5.659139e+05},
{943.000000, 0.141867, 5.443336e+05},
{944.000000, 0.142114, 5.855673e+05},
{945.000000, 0.142400, 5.668312e+05},
{946.000000, 0.142417, 4.445018e+05},
{947.000000, 0.142320, 5.999181e+05},
{948.000000, 0.142602, 5.575320e+05},
{949.000000, 0.143054, 8.448930e+05},
{950.000000, 0.143484, 9.458080e+05},
{951.000000, 0.143735, 7.989161e+05},
{952.000000, 0.144181, 5.080550e+05},
{953.000000, 0.144397, 7.626725e+05},
{954.000000, 0.144418, 4.820791e+05},
{955.000000, 0.144674, 4.483526e+05},
{956.000000, 0.145035, 6.073444e+05},
{957.000000, 0.145032, 5.502198e+05},
{958.000000, 0.145309, 7.544355e+05},
{959.000000, 0.145596, 7.535945e+05},
{960.000000, 0.145649, 5.061007e+05},
{961.000000, 0.146448, 3.876527e+05},
{962.000000, 0.146848, 3.790204e+05},
{963.000000, 0.146703, 4.363951e+05},
{964.000000, 0.146409, 6.740311e+05},
{965.000000, 0.146385, 4.144556e+05},
{966.000000, 0.146976, 4.314713e+05},
{967.000000, 0.147540, 4.437438e+05},
{968.000000, 0.148287, 6.681416e+05},
{969.000000, 0.148085, 3.914546e+05},
{970.000000, 0.148325, 6.922758e+05},
{971.000000, 0.148921, 6.051090e+05},
{972.000000, 0.149038, 7.302546e+05},
{973.000000, 0.149071, 8.401510e+05},
{974.000000, 0.149267, 8.968019e+05},
{975.000000, 0.149490, 5.237150e+05},
{976.000000, 0.149373, 4.619953e+05},
{977.000000, 0.150339, 7.847368e+05},
{978.000000, 0.150590, 1.111879e+06},
{979.000000, 0.150770, 8.388782e+05},
{980.000000, 0.150871, 7.966357e+05},
{981.000000, 0.150954, 1.092608e+06},
{982.000000, 0.151129, 8.113122e+05},
{983.000000, 0.151084, 5.613815e+05},
{984.000000, 0.151498, 7.328270e+05},
{985.000000, 0.152092, 5.069179e+05},
{986.000000, 0.152693, 4.903325e+05},
{987.000000, 0.153251, 8.081361e+05},
{988.000000, 0.153725, 1.205137e+06},
{989.000000, 0.153428, 7.358708e+05},
{990.000000, 0.153065, 5.143674e+05},
{991.000000, 0.153407, 4.991044e+05},
{992.000000, 0.153747, 6.122113e+05},
{993.000000, 0.154352, 6.535359e+05},
{994.000000, 0.154256, 1.034547e+06},
{995.000000, 0.154450, 3.695578e+05},
{996.000000, 0.155047, 6.474452e+05},
{997.000000, 0.155181, 3.050439e+05},
{998.000000, 0.155182, 3.537232e+05},
{999.000000, 0.155759, 6.017986e+05},
{1000.000000, 0.156483, 6.030601e+05}};

int i;

for (i=0; rdata[i][0]; i++)
	{
   l[i] = rdata[i][0];
	y[i] = rdata[i][1];
	}
}




