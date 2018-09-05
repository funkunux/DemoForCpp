#include <mysql/mysql.h>

#include "Logging.h"
#include "Demo.h"

void demo_mysql(void)
{
    MYSQL conn;
    mysql_init(&conn);
    if(mysql_real_connect(&conn, "localhost", "root", "fkh-138564", "DemoForCpp", 0, NULL, CLIENT_FOUND_ROWS))
    {
        DEMO_DEBUG("Connect Success!\n");
    }
    if (mysql_query(&conn, "SELECT id,password from session,user WHERE name=userName")) {
        std::cout << "查询失败" << std::endl;
        return;
    }
    std::cout << "查询成功" << std::endl;
    MYSQL_RES *result;
    result = mysql_store_result(&conn);
    if (result) {
        int row_num,col_num;
        row_num = mysql_num_rows(result);
        col_num = mysql_num_fields(result);
        std::cout << "共有" << row_num << "条数据，以下为其详细内容：" << std::endl;
        MYSQL_FIELD *fd;
        while (fd = mysql_fetch_field(result)) {
            std::cout << fd->name << "\t";
        }
        std::cout << std::endl;
        MYSQL_ROW sql_row;
        while (sql_row = mysql_fetch_row(result)) {
            for (int i = 0; i < col_num; i++) {
                if (sql_row[i] == NULL) std::cout << "NULL\t";
                else std::cout << sql_row[i] << "\t";
            }
            std::cout << std::endl;
        }
    }
    if(result!=NULL) mysql_free_result(result);


}