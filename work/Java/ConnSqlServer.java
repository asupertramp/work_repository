import java.sql.*;
public class ConnSqlServer {  
 
public static void main(String[] srg) {  
 
   String driverName = "com.microsoft.sqlserver.jdbc.SQLServerDriver";   //加载JDBC驱动  
//String url = "jdbc:sqlserver://"+ip+":"+port+";database="+databaseName+";user="+user+";password="+PWD;
   String dbURL = "jdbc:sqlserver://202.194.20.235:1433; databaseName=acms;user=lucyinthesky;password=ladymadonna2961737";   //连接服务器和数据库sample  
 
   Connection dbConn;  
 
   try {  
 
   Class.forName(driverName);  
 
   dbConn = DriverManager.getConnection(dbURL);  
 
   System.out.println("Connection Successful!");   //如果连接成功 控制台输出Connection Successful!  
 
   } catch (Exception e) {  
 
   e.printStackTrace();  
 
   }  
 
}  
 
} 