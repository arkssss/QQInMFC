#include "StdAfx.h"
#include "C_MysqlOpForServer.h"
#include "Msg.h"
#include "ConnectMap.h"
//静态变量声明处
Mysql_Op C_MysqlOpForServer::thMysql_Op;


C_MysqlOpForServer::C_MysqlOpForServer(void)
{
}


C_MysqlOpForServer::~C_MysqlOpForServer(void)
{
}

bool C_MysqlOpForServer::OperatorForLogIn(string Username,string Pwd){
	//登陆逻辑
		string sql="select * from RegUser where UserName ='"+Username+"' and PassWord ='"+Pwd+"' ";
		if(thMysql_Op.ExeSqlWithoutRes(sql)){
		
			if(thMysql_Op.result=thMysql_Op.ExeSqlWithRes(sql)){
				//查找成功则返回结果集
				thMysql_Op.sql_row=mysql_fetch_row(thMysql_Op.result);
				CMsg::SendMsg["UserName"]=thMysql_Op.sql_row[1];
				CMsg::SendMsg["PassWord"]=thMysql_Op.sql_row[2];
				CMsg::SendMsg["Age"]=thMysql_Op.sql_row[3];
				CMsg::SendMsg["Sex"]=thMysql_Op.sql_row[4];
				CMsg::SendMsg["RegTime"]=thMysql_Op.sql_row[6];
				CMsg::SendMsg["BusiStatus"]="1";
				return true;
			}
			
		}
		CMsg::SendMsg["BusiStatus"]="0";
		return false;

}


bool C_MysqlOpForServer::OperatorForGetList(string UserName){
		//返回好友列表逻辑 , 此步保证UserName存在于数据库中
		string sql= "select FriendName from HostFirend where HostName='"+UserName+"'";
		string FriendName;
		if(thMysql_Op.ExeSqlWithoutRes(sql)){
			//说明有好友
			thMysql_Op.result=thMysql_Op.ExeSqlWithRes(sql);				
				while(thMysql_Op.sql_row=mysql_fetch_row(thMysql_Op.result)){
				//获得好友的用户名
				FriendName=thMysql_Op.sql_row[0];
				string sql2="select CurrentStatus from RegUser where UserName='"+FriendName+"'";
				thMysql_Op.result2=thMysql_Op.ExeSqlWithRes(sql2);
				thMysql_Op.sql_row2=mysql_fetch_row(thMysql_Op.result2);
				CMsg::SendMsg[FriendName]=thMysql_Op.sql_row2[0];
					
			}
				//说明有好友
			CMsg::SendMsg["FriendType"]="1";
			return true;
		}
		//说明没有好有
		CMsg::SendMsg["FriendType"]="0";
		return false;
}