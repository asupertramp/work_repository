import java.sql.*;
public class ConnSqlServer {  
 
public static void main(String[] srg) {  
 
   String driverName = "com.microsoft.sqlserver.jdbc.SQLServerDriver";   //����JDBC����  
//String url = "jdbc:sqlserver://"+ip+":"+port+";database="+databaseName+";user="+user+";password="+PWD;
   String dbURL = "jdbc:sqlserver://202.194.20.235:1433; databaseName=acms;user=lucyinthesky;password=ladymadonna2961737";   //���ӷ����������ݿ�sample  
 
   Connection dbConn;  
 
   try {  
 
   Class.forName(driverName);  
 
   dbConn = DriverManager.getConnection(dbURL);  
 
   System.out.println("Connection Successful!");   //������ӳɹ� ����̨���Connection Successful!  
 
   } catch (Exception e) {  
 
   e.printStackTrace();  
 
   }  
 
}  
 
} 