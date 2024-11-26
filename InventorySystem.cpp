#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream> 
using namespace std;

sql::Connection* connectDatabase(){
	try{
		sql::mysql::MySQL_Driver *driver;
		sql::Connection *con; 

		driver = sql::mysql::get_mysql_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306","root","netacad");
		con->setSchema("InventorySystem");
		return con; 
	} catch (sql::SQLException &e) {
		cout << "Error connecting to Database: " << e.what() << endl;
		return nullptr;
	}
}
void addProduct(sql::Connection* con){
        string productName;
	int productPrice, stockQuantity; 
	cout << "Please insert product name: ";
        cin >> productName;
        cout << "\nPlease insert product price: ";
        cin >> productPrice;
        cout << "\nPlease insert stock quantitiy: ";
        cin >> stockQuantity;
	string QueryLine = "insert into Products (product_name,product_price,stock_quantity) VALUES (?,?,?)"; 
       	
	sql::PreparedStatement* pstmt = con->prepareStatement(QueryLine);
	pstmt->setString(1,productName);
	pstmt->setInt(2,productPrice);
	pstmt->setInt(3,stockQuantity);
	pstmt->executeUpdate(); 
	cout << "row added" << endl;
		
	
}

void updateProduct(sql::Connection* con){
	string productName, newProductName, query;
       	int newProductPrice, newStockCount, userInput;
	sql::PreparedStatement* pstmt; 		
	cout << "Please insert the product you would like to update: "; 
	cin >> productName; 
	do {
		cout << "\nWhat about " << productName << "you would like to update?" <<  endl;
		cout << "1. Product Name" << endl; 
		cout << "2. Product Price" << endl; 
		cout << "3. Stock Quantity" << endl;
		cout << "4. Exit" << endl; 
		cin >> userInput; 
		switch (userInput){
			case 1: 
				cout << "Insert the new product name: " << endl ; 
				cin >> newProductName;
				query = "UPDATE Products SET product_name = ? where product_name = ?; ";		
				pstmt = con->prepareStatement(query);

				pstmt->setString(1,newProductName);
				pstmt->setString(2,productName);
				pstmt->executeUpdate();
				break; 
			case 2: 
				cout << "Insert the new product price: " << endl ; 
				cin >> newProductPrice; 
				query = "UPDATE Products SET product_price = ? where product_name = ?; ";		
				pstmt = con->prepareStatement(query);

				pstmt->setInt(1,newProductPrice);
				pstmt->setString(2,productName);
				pstmt->executeUpdate();
				break; 
			case 3: 
				cout << "Insert the new stock quantity: " << endl ; 
				cin >> newStockCount; 
				query = "UPDATE Products SET stock_quantity = ? where product_name = ?; "	;	
				pstmt = con->prepareStatement(query);

				pstmt->setInt(1,newStockCount);
				pstmt->setString(2,productName);
				pstmt->executeUpdate();
				break;
			case 4: 
				return ; 
			default: 
				cout << "Invalid input" << endl ; 
			
		}
		


	}while(userInput!=4); 
	


}

void deleteProduct(sql::Connection* con){
	string productName; 
	cout << "What product would you like to delete? " << endl; 
	cin >> productName; 
	string query = "DELETE FROM Products where product_name = ? ;" ; 
	sql::PreparedStatement* pstmt = con->prepareStatement(query); 
	pstmt->setString(1,productName); 
	pstmt->executeUpdate(); 
}

void viewProduct(sql::Connection* con){
	string query = "select * from Products ; " ; 
	sql::PreparedStatement* pstmt = con->prepareStatement(query);  
	sql::ResultSet* res = pstmt->executeQuery(); 
	while (res->next()){
		cout << "Product Details: " << endl ;
		cout << "Product ID: " <<  res->getInt("product_id") << endl;
		cout << "Product Name: " << res->getString("product_name") << endl;
		cout << "Product price: " << res->getInt("product_price") << endl;
		cout << "Stock quantity: " << res->getString("stock_quantity") << endl;
	}
}	

int main(){
	sql::Connection* con = connectDatabase(); 

	int userInput; 
	cout << "MAIN MENU\n";
	cout << "1. Add product \n";
	cout << "2. Update Product \n";
	cout << "3. Delete Product \n"; 
	cout << "4. View Product\n";
	cout << "5. Exit\n";
	cin >> userInput; 

	switch(userInput){
		case 1: 
			addProduct(con); 
			break; 
		case 2: 
			updateProduct(con);
			break;
		case 3: 
			deleteProduct(con);
			break;
		case 4:
			viewProduct(con);
			break;
		case 5: 
			cout << "Goodbye \n"; 
			return 0; 
		default: 
			cout << "Invalid input"; 
	}

	return 0;
}	
