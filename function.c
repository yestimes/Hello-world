#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myfile.h"
									//用户
//完成，查找用户名
int find_userName_in_user(user *source, user **return_user, char *aim_str, int *bool_out)
{
	int ret = 0;
	user *p = source;
	//校验
	if (source == NULL){
		ret = -1;
		printf("find_userName_in_user: find user information is NULL \n");
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
			*return_user = p;
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
	if (p == NULL){
		ret = -1;
		printf("line 44 function check_passWord_in_user user information is NULL \n");
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
	
	return ret;
}
//完成，创建用户信息头
int set_user_head(user **head, char *user_str, char *passwd_str)
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
	return ret;
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
	user *p = NULL;
	//校验
	if ( head_in == NULL){
		ret = -1;
		printf("user_register err:link_list of user information is NULL \n");
		return ret;
	}
	//查询用户名称是否存在
	find_userName_in_user(start, &p, userName, &result);
	if (result == 1){
		*bool_return = 0;
		return ret;
	}
	ret = user_addback(start, userName, passWord);
	if (ret != 0){
		printf("line 132\n");
		*bool_return = 0;
		return ret;
	}
	*bool_return = 1;
	return 0;

}
//完成，检查用户名，密码(遍历链表）
int check_user_login(char *userName, char *passWord, int *state, user *user_infor, user **userid_return)
{
	int result = 0;
	user *p = NULL;
	if (userName == NULL || passWord == NULL || user_infor == NULL || userid_return == NULL){
		
		printf("err check_user_login:参数\n");
		return -1;
	}
	find_userName_in_user(user_infor, &p, userName, &result);

	if (result != 1){
		*userid_return = NULL;
		*state = -1;
		return 0;
	}
	if (p == NULL){
		printf("line 155\n");
	}
	check_passWord_in_user(p, passWord, &result);
	if (result != 1){
		*userid_return = NULL;
		*state = -2;
		return 0;
	}
	*userid_return = p;
	*state = 1;
	return 0;
}
									//文件
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
int load_userdata(struct user_inf **r, int *result_back)
{
	int ret = 0;
	int result = 0;
	int func_result = 0;
	int exit_sum = 1;
	int buf_count = 0;
	int run_count = 0;
	char str_temp[16];
	char key_user[16];
	char key_passwd[16];
	char *ptr = NULL;
	int buf_length = 0;
	int count = 0;
	//载入文件数据 
	FILE *fp = NULL;
	fp = fopen("..\\data\\user.txt","r+");
	if (fp == NULL){
		printf("err:open file fail\n");
		printf("press any key to continue\n");
		getchar();
		*result_back = 0;
		return -1;
	}
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
			count++;
			fgets(str_temp, 16, fp);
			if(!feof(fp)) {
				exit_sum = 0;
			}
			if (count >= 3){
				strcpy(str_temp, "null");
				break;
			}
		}
		count = 0;
		get_KEY_form_buf("user_name", key_user, str_temp, &buf_length);
		//密码
		while (exit_sum){
			//一定要读取到passwd关键字 
			fgets(str_temp, 16, fp);
			ptr = strstr(str_temp, "passwd");
			if (ptr != NULL){
				break;
				printf("do not break\n");
			}
			fgets(str_temp, 16, fp);
			count++;
			if (!feof(fp)) {
				break;
				exit_sum = 0;
			}
			if (count >= 3){
				strcpy(str_temp, "null");
				break;
			}
		}
		get_KEY_form_buf("passwd", key_passwd, str_temp, &buf_length);
		if (run_count == 0){
			set_user_head(r, key_user, key_passwd);
			run_count++;
			if (result != 1){
				printf("set user info head fail\n");
				return -1;
			}
			user_addback(*r, key_user, key_passwd);
		}
	}
	fclose(fp);
	return 0;
	
}
//没有完成，从文件载入房间数据
int load_roomdata(room **out_linkList, int *result)
{
	FILE *fp = NULL;
	fp = fopen("..\\data","r+");
	if (fp == NULL){
		printf("err:open files fail\n");
		*result = 0;
		return 0;
	}
	fclose(fp);
	return 0;
}

									//房间
//创建房间信息头
int set_room_head(const room **source, int *result)
{
	//校验
	if (source == NULL){
		printf("err:room head 's aderss is null\n");
		printf("press any key to continue\n");
		getchar();
		*result = 0;
		return -1;
	}
	room *p = NULL;
	p = (room *)malloc(sizeof(room));
	*source = p;
	//数据初始化
	p->id = 1;
	strcpy(p->name_guest, "null");
	p->head_book = NULL;
	p->next = NULL;
	p->price = 0;
	p->state = 2;
	p->t_start = 0;
	p->t_end = 1;

	*result = 1;
	return 0;
}
/*通过id寻找房间信息地址(遍历链表）*/
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
	while (p != NULL){
		if (key == p->id){
			*out_ptr = p;
			*result = 1;
			return ret;
		}
		p = p->next;
	}
	*out_ptr = NULL;
	*result = 1;
	return ret;
}
//通过id删除房间(遍历链表）
int delete_room_by_id(const int id, const room *head_info, int *result)
{
	room *p = head_info;
	room* p1 = NULL;
	room *p2 = NULL;
	room *p3 = NULL;
	//校验
	if (p == NULL){
		printf("err:room *head_info == NULL\n");
		return -1;
	}
	if (result == NULL){
		printf("err:int *result == NULL\n");
		return -1;
	}
	while (p != NULL){
		if (p->next->id == id){
			p1 = p;
			p2 = p->next->next;
			break;
		}
		p = p->next;
	}
	p1->next = p2;
	if (p != NULL){
		free(p);
		p = NULL;
	}
	return 0;
}
//完成，查看当前可用客房(遍历链表）
int find_free_room(room *h_start, int f_date, int s_date, int *list_result)
{
	int print_times = 0;
	int ret = 0;
	int outcome = 0;
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
	printf(" your reserch %5d to %5d \n", p->t_start, p->t_end);
	while (p != NULL){
		check_room_reserve(head, f_date, s_date, &outcome);
		printf("err:outcome == %d \n",outcome);
		if (outcome == 1 ){
			printf("%5d %s %d\n",p->id,state_to_string[p->state],p->price);
			print_times++;
		}
		p = p->next;
	}
	*list_result = print_times;
	return ret;
}
//添加房间
int room_add(const room *source, int id, int price, int *result)
{
	if (source == NULL){
		printf("err:room infomation is null\n");
		*result = 0;
		printf("press any key to continue\n");
		getchar();
		return -1;
	}
	room *p = source;
	room *r = NULL;
	while (p->next != NULL){
		p = p->next;
	}
	r = (room *)malloc(sizeof(room));
	r->next = NULL;
	r->head_book = NULL;
	r->id = id;
	strcpy(r->name_guest,"null");
	r->price = price;
	r->state = 0;
	r->t_end = 0;
	r->t_start = 0;
	p->next = r;

	*result = 1;
	return 0;
}
									//预订
//创建预订信息头
int set_reserve_head(const room *source, int *result)
{
	//check pointer is null or not
	if (source == NULL || result == 0){
		printf("err 494:trans room information == NULL\n");
		printf("press any key to continue\n");
		getchar();
		*result = 0;
		return -1;
	}
	room *p = source;
	room_book *ptr = NULL;
	p->head_book = (room_book *)malloc(sizeof(room_book));
	//初始化数据
	ptr = p->head_book;
	strcpy(p->head_book->name, "null");
	ptr->next = NULL;
	ptr->t_start = 20161231;
	ptr->t_end = 20170103;
	*result = 1;
	return 0;
}
//预定信息添加
int reserve_addback(room_book **head_book_ptr, const char *name, const int t_start, const int t_end, int *result)
{
	room_book *p = *head_book_ptr;
	room_book *r = NULL;
	room_book *temp = NULL;
	int outcome = 0;
	//校验
	if (p == NULL){
		printf("line 520 err:room_book information == NULL\n");
		printf("press any key to continue\n");
		getchar();
		*result = 0;
		return -1;
	}
	while (p != NULL){
		if (outcome == 0){
			if (t_end < p->t_start){
				outcome++;
				r = (room_book *)malloc(sizeof(room_book));
				r->next = p;
				*head_book_ptr = r;
				p = r;
				strcpy(p->name, name);
				p->t_start = t_start;
				p->t_end = t_end;
				break;
			}
		}
		else{
			if ((t_start < p->t_end) || (t_end < p->next->t_start)){
				r = (room_book *)malloc(sizeof(room_book));
				p->next = temp;
				p->next = r;
				r->next = temp;
				p = r;
				strcpy(p->name, name);
				p->t_start = t_start;
				p->t_end = t_end;
				outcome = 0;
				break;
			}
		}
		p = p->next;
		outcome++;
	}
	if (outcome > 1){
		*result = 0;
		printf("function call err: reserve_addback \n");
		printf("press any key to continue\n");
		getchar();
		return -1;
	}
	*result = 1;
	return 0;
}
//房间预订
int hotel_reserve(room *source,const char *name, int room_id_sn, int t_start, int t_end, int *result)
{
	room *p = NULL;//被房间节点赋值
	int outcome = 0;
	//校验
	if (source == NULL){
		printf("err:source of room == NULL\n");
		printf("press any key to continue\n");
		getchar();
		return -1;
	}
	find_room_by_id(room_id_sn, source, &p, &outcome);
	if (outcome == 0){
		printf("err:do not find room by id\n");
		printf("press any key to continue\n");
		getchar();
		*result = 0;
		return -2;
	}
	reserve_addback(&(p->head_book), name, t_start, t_end, result);
	*result = 1;
	return 0;
}
//完成，查询房间预订情况
int check_room_reserve(const room *info, const int t_start, const int t_end, int *result)
{
	room_book *p = info->head_book; 
	int count = 0;
	//校验
	if (info == NULL){
		printf("err:room *information == NULL\n");
		printf("press any key to continue\n");
		getchar();
		*result = 0;
		return -1;
	}
	if (p == NULL){
		printf("err:room book == NULL\n");
		printf("press any key to continue\n");
		getchar();
		*result = 0;
		return -1;
	}
	while (p->next != NULL){
		if (count == 0){
			if (t_end < p->t_start){
				*result = 1;
				return 0;
			}
			count++;
		}
		else{
			if ( (t_start > p->t_end) || (t_end < p->next->t_start)){
				*result = 1;
				return 0;
			}
		}
	}
}
//完成，入住
int check_in(int room_id_sn, room *source, const char *name, int t_start, int t_end, int *result)
{
	room *p = NULL;
	find_room_by_id(room_id_sn, source, &p, result);
	if (*result == 0){
		printf("err:do not find it\n");
		*result = 0;
		return -1;
	}
	strcpy(p->name_guest, name);
	p->t_start = t_start;
	p->t_end = t_end;
	*result = 1;
	return 0;
}
//修改客房指定信息
int edit_room(const room *head_info,const int chose, int id, char *name_guest, int state, int price, int t_start, int t_end, int *result)
{
	//校验
	if (head_info == NULL){
		printf("head of room information is null, please check it \n");
		return -1;
	}
	room *head = head_info;
	room *p = NULL;
	find_room_by_id(id, head_info, &p, result);
	if (result == 0){
		printf("err:do not find it\n");
		*result = 0;
		return -1;
	}
	switch (chose){
		case 0:
			strcpy(p->name_guest, name_guest);
			break;
		case 1:
			p->state = state;
			break;
		case 2:
			p->price = price;
			break;
		case 3:
			p->t_start = t_start;
			break;
		case 4:
			p->t_end = t_end;
			break;
		default:
			printf("input err\n");
			*result = 0;
	}
	*result = 1;
	return 0;
}
//完成，释放用户信息
int free_user(const user *start, int *result)
{
	//校验
	if (start == NULL){
		printf("err:user of link-list head is null\n");
		*result = 0;
		printf("press any key to continue\n");
		getchar();
	}
	user *p = start;
	user *r = NULL;
	while (p != NULL){
		r = p->next;
		if (p != NULL){
			free(p);
		}
		p = r;
	}
	*result = 1;
	return 0;
}
//完成，释放预定
int free_reserve(const room *head_info, int *result)
{
	room_book *p = head_info->head_book;
	room_book *r = NULL;
	//校验
	if (head_info== NULL){
		printf("err:room of link-list head is null\n");
		*result = 0;
		printf("press any key to continue\n");
		getchar();
	}
	while ( p != NULL){
		r = p->next;
		if (p != NULL){
			free(p);
		}
		p = r;
	}
	*result = 1;
	return 0;
}
//完成，释放客房
int free_all_room(const room *head_info, int *result)
{
	room *p = head_info;
	room *r = NULL;
	int ret = 0;
	if (head_info == NULL){
		printf("err:room of link-list head is null\n");
		*result = 0;
		printf("press any key to continue\n");
		getchar();
		return -1;
	}
	//释放所有房间下的预定
	while (p != NULL){
		free_reserve(p, &ret);
		if (ret == 0){
			printf("err:free %p id :%d is fail\n");
			*result = 0;
			printf("press any key to continue\n");
			getchar();
			break;
			return -1;
		}
		p = p->next;
	}
	//释放所有房间
	p = head_info;
	while (p != NULL){
		r = p->next;
		free(p);
		p = r;
	}
	*result = 1;
	return 0;
}
//客房按id排序(sort by bubble)
int sort_room_by_id(const room *start, int *result)
{
	room temp;
	room *p = NULL;
	room *r = NULL;
	if (start == NULL){
		printf("err:information is null\n");
		printf("press any key to continue\n");
		getchar();
		*result - 0;
		return -1;
	}
	p = start;
	while (p != NULL){
		r = p;
		while (r != NULL){
			if (p->id > r->id){
				temp = *p;
				*p = *r;
				*r = temp;
			}
			r = r->next;
		}
		p = p->next;
	}
	*result = 1;
	return 0;
}
//结束程序
int exit_manger_system(const user *p_str, const room *r_str, int *result)

{
	free_user(p_str, result);
	if (*result != 1){
		printf("free user err 请关闭后重启计算机，避免内存泄漏\n");
		*result = 1;
		return -1;
	}
	free_all_room(r_str, result);
	if (*result != 1){
		printf("free room err 请关闭后重启计算机，避免内存泄漏\n");
		*result = 1;
		return -1;
	}
	*result = 1;
	return 0;
}