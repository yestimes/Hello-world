#ifndef _STDIO_H_
#include <stdio.h>
#endif
#ifndef _STDLIB_H_
#include <stdlib.h>
#endif
#ifndef _STRING_H_
#include <string.h>
#endif
#ifndef _MYFILE_H_
#include "myfile.h"
#endif
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

//完成，查找用户名
int find_userName_in_user(user *source, user **return_user, char *aim_str, int *bool_out)
{
	int ret = 0;
	user *p = source;
	//校验
	if (source == NULL){
		ret = -1;
		printf(" user information is NULL \n");
		*bool_out = 0;
		return ret;
	}
	if (aim_str == NULL){
		ret = -2;
		printf("err:string of your aim is NULL \n");
		*bool_out = 0;
		return ret;
	}
	while (p != NULL){
		if ( strcmp(p->name,aim_str) == 0){
			*bool_out = 1;
			return 0;
		}
		p = p->next;
	}
	*bool_out = 0;
	return ret;
}
//完成，校验密码
int check_passWord_in_user(user *source, char *aim_str, int *bool_out)
{
	int ret = 0;
	user *p = source;
	//校验
	if (source == NULL){
		ret = -1;
		printf(" user information is NULL \n");
		*bool_out = 0;
		return ret;
	}
	if (aim_str == NULL){
		ret = -2;
		printf("err:passwd of your aim is NULL \n");
		*bool_out = 0;
		return ret;
	}
	if (strcmp(p->passwd, aim_str) == 0){
		*bool_out = 1;
		return 0;
	}
	/*while (p != NULL){
		if (strcmp(p->passwd, aim_str) == 0){
		*bool_out = 1;
		return 0;
		}
		p = p->next;
		}*/
	return ret;
}
//完成，创建用户信息头
int set_user_head(user **head, char *user_str, char *passwd_str, int *result)
{
	int ret = 0;
	if( (head == NULL) || (user_str == NULL) || (passwd_str == NULL)){
		printf("err:user **head == NULL or char *user_str == NULL or  char *passwd_str == NULL");
		ret = -1;
		return ret;
	}
	user *p = NULL;
	p = (user *)malloc(sizeof(user));
	strcpy(p->name,user_str);
	strcpy(p->passwd,passwd_str);
	p->next = NULL;
	*head = p;
	*result = 1;
	return ret;
}
//创建预订信息头
int hotel_reserve(int room_id, int t_start, int t_end, int *result)
{

}
//完成，用户添加
int user_addback(user *head, char *user_str, char *passwd_str)
{
	int ret = 0;
	if ( head == NULL){
		ret = -1;
		printf("err:user *head == NULL\n");
		return ret;
	}
	if ( user_str == NULL){
		printf("err:char *user_str == NULLL\n");
		return -1;
	}
	if ( user_str == NULL){
		printf("err:char *key_value_str == NULL\n");
		return -1;
	}
	if ( passwd_str == NULL){
		printf("err:char *passwd_str == NULL == NULL\n");
		return -1;
	}
	user *start = head;
	user *p = head;
	while((p->next) != NULL){
		p = p->next;
	}
	strcpy(p->name,user_str);
	strcpy(p->passwd,passwd_str);
	p->next = NULL;
	return 0;
}
//完成，用户注册
int user_register(user *head_in, char *userName, char *passWord, int *bool_return)
{
	int ret = 0;
	int result = 0;
	user *start = head_in;
	//校验
	if ( head_in == NULL){
		ret = -1;
		printf("err:link_list of user information is NULL \n");
		return ret;
	}
	//查询用户名称是否存在
	ret = find_string_in_user(start, userName, &result);
	if (result == 0){
		*bool_return = 1;
		return ret;
	}
	ret = user_addback(start, userName, passWord);
	if (ret == 0){
		*bool_return = 0;
		return ret;
	}
	*bool_return = 1;
	return -1;

}
//完成，从文件获取关键字
int get_KEY_form_buf(char *key_str, char *value_str, char *key_value_str, int  *value_buf_length)
{
	char *ptr = NULL;
	//校验
	if (key_str == NULL){
		printf("err:char *key_str == NULL\n");
		return -1;
	}
	if (value_str == NULL){
		printf("err:char *value_str == NULL\n");
		return -1;
	}
	if (key_value_str == NULL){
		printf("err:char *key_value_str == NULL\n");
		return -1;
	}
	if (value_buf_length == NULL){
		printf("err: int *value_buf_length == NULL\n");
		return -1;
	}
	//转接
	ptr = key_value_str;
	//找关键字
	ptr = strstr(ptr, key_str);
	if (ptr == NULL){
		return -1;
	}
	//找等号
	while ((*ptr) != '=' && (*ptr) != '\0'){
		ptr++;
	}
	ptr++;
	//调用去除空格处理
	dislodge_blank_from_str(ptr, value_str);
	//计算长度
	*value_buf_length = strlen(value_str);
	return 0;
}
//完成，字符串处理，去除两头的空格 
int dislodge_blank_from_str(char *source_str, char *output_buffer)
{
	char *p = source_str;
	char *r = output_buffer;
	if (source_str == NULL){
		printf("err:source_str == NULL\n");
		return -1;
	}
	if (output_buffer == NULL){
		printf("err:output_buffer == NULL\n");
		return -1;
	}
	int i = 0;
	char temp[200] = { 0 };
	while ((*p) != '\0'){
		if ((*p) != ' '){
			temp[i] = (*p);
			i++;
		}
		p++;
	}
	temp[++i] = '\0';
	i = 0;

	while (temp[i] != '\0'){
		(*r++) = temp[i++];
	}
	*(++r) = '\0';
	return 0;
}
//没有完成，从文件载入用户数据
int load_userdata(struct user_inf **r, int *result)
{
	int ret = 0;
	int func_result = 0;
	int exit_sum = 1;
	int buf_count = 0;
	int run_count = 0;
	char str_temp[16];
	char key_user[16];
	char key_passwd[16];
	char *ptr = NULL;
	int buf_length = 0;
	//载入文件数据 
	FILE *fp = NULL;
	fp = fopen("E:\\project_doucment\\data\\user.txt","r+");
	//读取完文件才行 
	while( !feof(fp)) {
		//校验
		if(fp == NULL){
			printf("err:load data fail, user data file can not open \n");
			ret = -1;
			return ret;
		}
		while (exit_sum){
			//一定要读取到user_name关键字 
			fgets(str_temp, 16, fp);
			ptr = strstr(str_temp, "user_name");
			if (ptr != NULL){
				break;
				printf("do not break\n");
			}
			fgets(str_temp, 16, fp);
			if(!feof(fp)) {
				exit_sum = 0;
			}
		}
		get_KEY_form_buf("user_name", key_user, str_temp, &buf_length);
		//用户名
		while (exit_sum){
			//一定要读取到passwd关键字 
			fgets(str_temp, 16, fp);
			ptr = strstr(str_temp, "passwd");
			if (ptr != NULL){
				break;
				printf("do not break\n");
			}
			fgets(str_temp, 16, fp);
			if (!feof(fp)) {
				break;
				exit_sum = 0;
			}
		}
		get_KEY_form_buf("passwd", key_passwd, str_temp, &buf_length);
		if (run_count == 0){
			set_user_head(r, key_user, key_passwd, &result);
			run_count++;
			if (result != 1){
				printf("set user info head fail\n");
				return -1;
			}
			user_addback(*r, key_user, key_passwd);
		}
	}
	fclose(fp);
	*result = 1;
	return 0;
	
}
//没有完成，从文件载入房间数据
int load_userdata(room **out_linkList, int *result)
{
	int ret = 0;
	int func_result = 0;
	int exit_sum = 1;
	int buf_count = 0;
	int run_count = 0;
	char str_temp[16];
	char key_user[16];
	char key_passwd[16];
	char *ptr = NULL;
	int buf_length = 0;
	//载入文件数据 
	FILE *fp = NULL;
	fp = fopen("E:\\project_doucment\\data\\user.txt", "r+");
	//读取完文件才行 
	while (!feof(fp)) {
		//校验
		if (fp == NULL){
			printf("err:load data fail, user data file can not open \n");
			ret = -1;
			return ret;
		}
		while (exit_sum){
			//一定要读取到user_name关键字 
			fgets(str_temp, 16, fp);
			ptr = strstr(str_temp, "user_name");
			if (ptr != NULL){
				break;
				printf("do not break\n");
			}
			fgets(str_temp, 16, fp);
			if (!feof(fp)) {
				exit_sum = 0;
			}
		}
		get_KEY_form_buf("user_name", key_user, str_temp, &buf_length);
		//用户名
		while (exit_sum){
			//一定要读取到passwd关键字 
			fgets(str_temp, 16, fp);
			ptr = strstr(str_temp, "passwd");
			if (ptr != NULL){
				break;
				printf("do not break\n");
			}
			fgets(str_temp, 16, fp);
			if (!feof(fp)) {
				break;
				exit_sum = 0;
			}
		}
		get_KEY_form_buf("passwd", key_passwd, str_temp, &buf_length);
		if (run_count == 0){
			set_user_head(r, key_user, key_passwd, &result);
			run_count++;
			if (result != 1){
				printf("set user info head fail\n");
				return -1;
			}
			user_addback(*r, key_user, key_passwd);
		}
	}
	fclose(fp);
	*result = 1;
	return 0;
}
//完成，检查用户名，密码(遍历链表）
int check_user_login(char *userName, char *passWord, int *state, user *user_infor, user **userid_return)
{
	int result = 0;
	user *p = NULL;
	find_userName_in_user(user_infor, &p, userName, &result);
	if (result != 1){
		*userid_return = NULL;
		*state = -1;
		return 0;
	}
	check_passWord_in_user(p, passWord, &result);
	if (result != 1){
		*userid_return = NULL;
		*state = -2;
		return 0;
	}
	*state = 1;
	return 0;
}
//完成，查看当前可用客房(遍历链表）
int find_free_room(room *h_start, int f_date, int s_date, int *list_result)
{
	int print_times = 0;
	char *state_to_string[3] = { "free", "using", "wait" };
	room *head = h_start;
	int start = f_date;
	int finish = s_date;
	room *p = h_start;
	//校验
	if (h_start == NULL){
		printf("err:source_str == NULL\n");
		return -1;
	}
	printf("--id-----state------price-----\n");
	printf(" your reserch %5d to %5d ",p->t_start, p->t_end);
	while (p != NULL){
		if (p->state == 0){
			printf("%5d %s %5d \n", p->id, state_to_string[p->state], p->price/*, p->t_start, p->t_end*/);
			print_times++;
		}
		p = p->next;
	}
	*list_result = print_times;
	return 0;
}
//通过id寻找房间信息地址(遍历链表）
int find_room_by_id(int id, room *head_info, room **out_ptr, int *result)
{
	int key = id;
	int ret = 0;
	room *p = head_info;
	if (out_ptr == NULL){
		ret = -1;
		printf("err:room out_ptr is NULL\n");
		return ret;
	}
	if (id < 0){
		ret = -1;
		printf("err:room id is NULL\n");
		return ret;
	}
	while ( p != NULL){
		if (key == p->id){
			*out_ptr = p;
			*result = 1;
			return ret;
		}
		p = p->next;
	}

}
//完成，从文件里获取用户名
int get_userName_string(const char *source, const char end_sign, char *outbuf,int *buf_length,  int *result)
{
	char *str = source;
	int ret = 0;
	char *c = end_sign;
	char temp_buf[32];
	int str_count = 0;
	//校验
	if (outbuf == NULL){
		printf("err:char *outbuffer == NULL\n");
		return -1;
	}
	if (source == NULL){
		printf("err:char *string == NULL\n");
		return -1;
	}
	if (end_sign == NULL){
		printf("err:char *end_sign == NULL\n");
		return -1;
	}
	if (result == NULL){
		printf("err:int *key_value_str == NULL\n");
		return -1;
	}
	while ((*str) != c && (*str) != '\0'){
		if (*(str) != ' '){
			temp_buf[str_count] = *str;
			str_count++;
		}
	}
	strcpy(outbuf, temp_buf);
	*buf_length = str_count;
	*result = 1;
	return ret;
}

//通过id删除房间(遍历链表）
int delete_room_by_id(const int id, const room *head_info, int *result)
{ 
    room *p = head_info;
    room* p1 = NULL, p2 = NULL, p3 = NULL;
    while (p != NULL){
        if (p->next->id == id){
            
         }
    }
}	
	
	
	
	
	
	
	
