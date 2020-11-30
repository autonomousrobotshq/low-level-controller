# Sandbox

bool	Driver(e_corner corner, e_drive_action action);

int		IMUGetNavigationAngle();

Vec3	IMUGetMagnetoData();

Vec3	IMUGetAcceleroData();

int		USGetDistance(e_corner corner);

void	GPSGetLocation(float *flat, float *flon);

void	GPSGetTime(unsigned long *age, unsigned long *date, unsigned long *time);

int		GPSGetSpeed();

int		GPSGetCourse();

int8_t	TEMPGetTemp();

int		RAMGetFree();

