typedef struct user_inf{
	char name[16];
	char passwd[16];
	struct user_inf *next;
}user;
typedef struct room_book{
	int t_start;
	int t_end;
	char name[16];
	struct room_book *next;
}room_book;
typedef struct hotel_room{
	int id;
	char name_guest[16];
	int state;
	int price;
	int t_start;
	int t_end;
	room_book *head_book;
	struct hotel_room *next;
}room;

int find_userName_in_user(user *source, user **return_user, char *aim_str, int *bool_out);
int check_passWord_in_user(user *source, char *aim_str, int *bool_out);
int set_user_head(user **head, char *user_str, char *passwd_str);
int user_addback(user *head, char *user_str, char *passwd_str);
int user_register(user *head_in, char *userName, char *passWord, int *bool_return);
int get_KEY_form_buf(char *key_str, char *value_str, char *key_value_str, int  *value_buf_length);
int dislodge_blank_from_str(char *source_str, char *output_buffer);
int load_userdata(struct user_inf **r);
int load_roomdata(room **out_linkList, int *result);
int check_user_login(char *userName, char *passWord, int *state, user *user_infor, user **userid_return);
int find_room_by_id(int id, room *head_info, room **out_ptr, int *result);
int find_free_room(room *h_start, int f_date, int s_date, int *list_result);
int hotel_reserve(room *source, const char *name, int room_id_sn, int t_start, int t_end, int *result);
int reserve_addback(room_book **head_book_ptr, const char *name, const int t_start, const int t_end, int *result);


