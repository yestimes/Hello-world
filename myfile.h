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
}book_room;
typedef struct hotel_room{
	int id;
	char name_guest;
	int state;
	int price;
	int t_start;
	int t_end;
	book_room *head_info;
	struct hotel_room *next;
}room;
//完成，从文件里获取用户名
//int get_userName_string(const char *source, const char end_sign, char *outbuf,int *buf_length,  int *result)
//{
//	char *str = source;
//	int ret = 0;
//	char c = end_sign;
//	char temp_buf[32];
//	int str_count = 0;
//	//校验
//	if (outbuf == NULL){
//		printf("err:char *outbuffer == NULL\n");
//		return -1;
//	}
//	if (source == NULL){
//		printf("err:char *string == NULL\n");
//		return -1;
//	}
//	if (result == NULL){
//		printf("err:int *key_value_str == NULL\n");
//		return -1;
//	}
//	while ((*str) != c && (*str) != '\0'){
//		if (*(str) != ' '){
//			temp_buf[str_count] = *str;
//			str_count++;
//		}
//	}
//	strcpy(outbuf, temp_buf);
//	*buf_length = str_count;
//	*result = 1;
//	return ret;
//}
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
int hotel_reserve(int room_id, int t_start, int t_end, int *result);

