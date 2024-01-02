class RegistryClass {
public:
	static void Init();
	static LONG loadSystemHive();
	static LONG loadSoftwareHive();
	static LONG loadDefaultHive();
	static LONG loadSystemUserHive();

	static bool unloadSystemHive();
	static bool unloadSoftwareHive();
	static bool unloadDefaultHive();
	static bool unloadSystemUserHive();
private:
	const char *driveletter;
	const wchar_t *lpSystemKey;
	const wchar_t *lpSoftwareKey;
	const wchar_t *lpDefaultKey;
	const wchar_t *lpSystemUserKey;
};