LONG loadSystemHive();
LONG loadSoftwareHive();
LONG loadDefaultHive();
LONG loadSystemUserHive();

bool unloadSystemHive();
bool unloadSoftwareHive();
bool unloadDefaultHive();
bool unloadSystemUserHive();

bool SetPermanentEnvironmentVariable(LPCTSTR value, LPCTSTR data);