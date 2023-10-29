#ifndef USER_FRIENDLY_H
#define USER_FRIENDLY_H

extern int user_interface;
#define UF_PRINT(...) if (user_interface) printf(__VA_ARGS__)

#endif