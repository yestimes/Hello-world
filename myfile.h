#define _CRT_SECURE_NO_WARNINGS
typedef struct user_inf{
	char name[16];
	char passwd[16];
	struct user_inf *next;
}user;
typedef struct hotel_room{
	int id;
	char name_guest;
	int state;
	int price;
	int t_start;
	int t_end;
	reserve *head_info;
	struct hotel_room *next;
}room;
typedef struct room_book{
	int t_start;
	int t_end;
	char name[16];
	int price;
	struct room_book *next;
}reserve;
//typedef struct mem_user{
//	user *ptr;
//	struct mem_user *next;
//}user_ptr;
//typedef struct mem_room{
//	room *ptr;
//	struct mem_user *next;
//}room_ptr;
int user_register(user *head_in, char *userName, char *passWord, int *bool_return);
int load_userdata(user **, int *result);
int welcome_system(void);
int find_room(room *object, char *condition);
int dislodge_blank_from_str(char *source_str, char *output_buffer);
int check_passWord_in_user(user *source, char *aim_str, int *bool_out);
int check_user_login(char *userName, char *passWord, int *state, user *user_infor, user **state_return);

