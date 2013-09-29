#ifndef DEF_H_
#define DEF_H_

#include <android/log.h>
#include <zip.h>

extern zip* APKArchive;

#define STRINGIFY(x) #x
#ifndef LOG_TAG
	#define LOG_TAG    __FILE__ ":" STRINGIFY(__LINE__)
#endif

#ifndef LOGI
	#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#endif

#ifndef LOGE
	#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#endif

#endif /* DEF_H_ */
