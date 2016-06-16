#include<iostream>
#include<cmath>
#include<math.h>
using namespace std;

class matrix{
public:

	int row_num;  
	int col_num;
	float **mat;

	matrix()    
	{
		row_num=0;
		col_num=0;
		mat=NULL;
		
	}


	matrix(const int r,const int c)				// r = no of rows . c = no of cols
	{
		if(r>0 &&c>0)	
		{
			row_num=r;
			col_num=c;
			mat=new float*[row_num];
			for(int i=0;i<row_num;i++)
			{
				mat[i]=new float[col_num];

			}

			for(int i=0; i<row_num;i++)
			{
				for(int j=0;j<col_num;j++)
				{
					mat[i][j]=0;
				}
			}
		}
	}
		
	virtual ~matrix()
	{
		for(int i=0;i<row_num;i++)
		{delete[] mat[i];}
			delete[] mat;
	}


	void setmatrix() // to set the rows and columns of matrix
	{
		cout<<"WRITE THE FOLLOWING:"<<endl;

	a:				// label where to shift the control of the program in case of evil row no input from user
		cout<<"Number of Rows:";
		cin>>row_num;

		// check if the input is evil ;)
		if(row_num < 1 || !(cin.good()))
				{
				cin.clear();			   // clear error condition
				cin.ignore(100,'\n');  // remove characters
				cout << "\nPlease enter an integer value of row no > 0 \n";
				goto a;
				}


	b:				// label where to shift the control of the program in case of evil col no input from user
		cout<<endl<<"Number of columns:";
		cin>>col_num;

		// check if the input is evil
		if(col_num < 1 || !(cin.good()))
				{
				cin.clear();			// clear error condition
				cin.ignore(100,'\n');  // remove characters
				cout << "\nPlease enter an integer value of col no > 0 \n";
				goto b;
				}

        cout<<endl<<"Write a "<<row_num<<"x"<<col_num<<" matrix :"<<endl;
		
		int val; // matrix data input storage variable
		mat=new float*[row_num];
 		for(int i=0;i<row_num;i++)
		{
			mat[i]=new float[col_num];
		}

		for(int i=0;i<row_num;i++)
		{
			cout <<endl<<"enter values for row " << i << " , each followed by 'enter':" << endl;
			for(int j=0;j<col_num;j++)
			{
				c:			// label to transfer control if the user inputs an evil input in the matrix data
				cin>>val;
				if(cin.good()!=0)
				mat[i][j]=val;
				else
				{
					cin.clear();			// clear error condition
					cin.ignore(100,'\n');  // remove characters
					cout<<" Value must be an integer-- \n enter again ";
					goto c;
				}
			}
			cout<<endl;
		}
	}

	void display() // for the display of matrix
	{
		for(int i=0;i<row_num;i++)
		{
			for(int j=0;j<col_num;j++)
			{
				cout<<" "<<mat[i][j];
			}
			cout<<endl;
		}
	}

	int get_rows()
	{
		return row_num;
	}
	int get_cols()
	{
		return col_num;
	}	

	virtual void division_matrix(int n)
	{}

	virtual void negative_matrix()
	{}
	
	virtual float trace_matrix()
	{return 0;}

};


class basic_functions:public matrix //basic_functions derived from the base class matrix
{
public:
	basic_functions():matrix()
	{}

	basic_functions(const int r,const int c):matrix(r,c)
	{}

	virtual ~basic_functions()
	{}
	
	friend basic_functions operator+(basic_functions& a,basic_functions& b);
	friend basic_functions operator-(basic_functions& a,basic_functions& b);
	friend basic_functions operator*(basic_functions& a,basic_functions& b);
	
	virtual void division_matrix(int n) // for the division of elements of a matrix with any no.
		{
			
			for(int i=0;i<row_num;i++)
			{
				for(int j=0;j<col_num;j++)
				{
					mat[i][j] =  mat[i][j] / n ;
				}
			}
		}




	virtual void negative_matrix() // to take the negative of a matrix
	{
		
			for(int i=0;i<row_num;i++)
			{
				for(int j=0;j<col_num;j++)
				{
					mat[i][j] = (-1) * mat[i][j];
				}
			}
	}


	virtual float trace_matrix() // for taking trace of the matrix
	{
		float a=0;
			for(int i=0;i<row_num;i++)
			{
				for(int j=0;j<col_num;j++)
				{
					if(i==j)
					{
						a = a + mat[i][j]; // addition of the diagonal enteries
					}
				}
			}
			return a;// returning sum of the diagonal entries
	}

	
};

basic_functions operator+(basic_functions& a,basic_functions& b)// for adding matrices
	{



		if(b.row_num!=a.row_num || b.col_num!=a.col_num)// checking possibility of addition
		{
			cout<<"Addition of these two matrices is not possible.:("<<endl;
			basic_functions temp(0,0);
			return temp;
		}
		else
		{
			basic_functions temp(a.row_num,a.col_num);//object of class basic_functions is created
			for(int i=0;i<a.row_num;i++)
			{
				for(int j=0;j<a.col_num;j++)
				{
					temp.mat[i][j] = a.mat[i][j] + b.mat[i][j];// addition of the corresponding elements of NxN matrices
				}
			}
			return temp;
		}

	}

basic_functions operator-(basic_functions& a,basic_functions& b)//for subtracting matrices
	{


		if(b.row_num==a.row_num && b.col_num==a.col_num)//checking condition for the possibility of subtraction
		{
			basic_functions temp(a.row_num,a.col_num);//object of class basic_functions created
			
			for(int i=0;i<a.row_num;i++)
			{
				for(int j=0;j<a.col_num;j++)
				{
					temp.mat[i][j] = a.mat[i][j] - b.mat[i][j];// difference of corresponding elements of given matrices
				}
			}
			return temp;
		}
		else
		{
			cout<<"Subtraction of these two matrices is not possible.:("<<endl;
			basic_functions temp(0,0);
			return temp;
		}


	}

basic_functions operator*(basic_functions& a,basic_functions& b)// for multiplication of matrices
		{
			if(a.col_num != b.row_num)// checking possibility of multiplication
			{
				cout<<"Multiplication of these two matrices is not possible.:("<<endl;
				basic_functions temp(0,0);//object of class basic_functions created
				return temp;
			}
			else
			{
				basic_functions temp(a.row_num,b.col_num);//object of class basic_functions created
				
				for(int i=0;i<a.row_num;i++)//loop from 0 to row_num of the first matrix
				{
					for(int j=0;j<b.col_num;j++)//loop from 0 to col_num of the 2nd matrix
					{
						temp.mat[i][j]=0;
						for(int k=0;k<a.col_num;k++)//k iss the col_num of the 2nd matrix
						{
							temp.mat[i][j]+=(a.mat[i][k]*b.mat[k][j]);//formula for multiplication of matrices
						}
					}
				}
				return temp;//returning object of class basic_functions
			}
			
		}




class special_functions:public matrix{//class special_functions derived from base class matrix
public:
	special_functions():matrix()
	{}
	special_functions(const int r,const int c):matrix(r,c)
	{}

	virtual ~special_functions()
	{}

	special_functions take_minor(const int r,const int c)//for taking minor of matri
	{       
			if(row_num>=3)//coz minor is poosible for matrices of order 3x3 or higher only
			{
				int a,b,i,j;
				if(r>=0 && r<row_num && c>=0 && c<col_num)
				{
					a=b=0;
					special_functions temp(row_num-1,col_num-1);// object created of class special_functions
					for(int i=0;i<row_num;i++)
					{	
						if(i!=r)
						{
							b=0;
							for(int j=0;j<col_num;j++)
							{
								if(j!=c)
								{
									
									temp.mat[a][b] = mat[i][j];// filling the elements of the minor matrix with rows 
									b++;					   //and columns one less than the original each
								}
							}
							a++;
						}
						
					}
				return temp; // returning object of class special_functions
				}
				else
				{
					cout<<"index of minor out of range."<<endl<<endl;
				}
			}
			else
			{
				cout<<"Minor of the given matrix is not possible"<<endl;
				special_functions temp(0,0);
				return temp;
			}

	}
	float det()//for finding the determinant
	{
		float d=0;
		int r,c;
		r=row_num;
		c=col_num;

		if(r==c)
		{
			if(r==1)//determinant of 1x1 matrix
			{
				d=mat[0][0];//equal to the only element of the matrix
			}
			
			else if(r==2)  //2x2 matrix
			{
				d = (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
			}

			else //3x3 or larger matrix
			{
				for (int i=0;i<r;i++)
				{
					special_functions temp(row_num-1,col_num-1);//creating object of class special_functions
					temp = take_minor(0,i); 
					if((i%2)==0)//checking if row_num is even
						d= d+mat[0][i]* temp.det();//determinant of minor takes + sign
					else
						d=d-mat[0][i]* temp.det();//determinant of minor takes - sign if row_num is odd
				}
			}
		}
		else
		{
			cout<<"Matrix must be square"<<endl<<endl;
		}
		return d;
	}
	float take_cofactor(const int r,const int c)// for taking individual cofactors of a matrix
	{
		if(row_num>=3)//checking condition 
		{
			int t=1;
			float cofctr;
			if(r>=0 && r<row_num && c>=0 && c<col_num)
			{
				special_functions temp(row_num,col_num);//object of class special_functions created
				temp=take_minor(r,c);// function of minor being called
				if((r+c)%2==0)
				{
					cofctr= t * temp.det();//if sum of row_num and col_num to b omitted 
					return cofctr;         //is even then minor gets multiplied with +1
				}
				else
				{
					t=-1;
					cofctr= t * temp.det();//if sum of row_num and col_num to b omitted 
					                       //is odd then minor gets multiplied with -1
					return cofctr;
				}
			}
		}
		else
		{
			cout<<"cofactor not possible"<<endl;
			return 0.0;
		}
	}
	special_functions take_cofactor_matrix()//to get the cofactor matrix 
	{
		if(row_num>=3)//to check the condition to carry out the function
		{
			int t=1;
			special_functions temp1(row_num,col_num);//object of class special_functions being created
			for(int i=0;i<row_num;i++)
			{
				for(int j=0;j<col_num;j++)
				{
					special_functions temp2=take_minor(i,j);//another object of class special_functions being created whose monor is taken
					temp1.mat[i][j] = t * temp2.det( );// the determinant of the minor gets multiplied with 1 and -1 alternatively
					cout<<endl;
					t=t*(-1);
				}
			}
			return temp1;// returning object of class special_functions
		}
		else
		{
			cout<<"cofactor matrix not possible"<<endl;
			special_functions temp(0,0);
			return temp;
		}

	}




	special_functions set_transpose()// for taking transpose of a matrix
		{
			special_functions temp(row_num,col_num);//creating object of class special_functions						
		
			for(int i=0;i<row_num;i++)
			{
				for(int j=0;j<col_num;j++)
				{
					if(i!=j)
					{
						
						temp.mat[i][j] = mat [j][i];// if row number and column number are not equal the elements get interchanged
					}
					else
					{
						
						temp.mat[i][j] = mat [i][j];// if row number and column number are equal the elements remain unchanged

					}
				}
			}
			return temp;
		}
			virtual bool is_square()//virtual function to check if the number of rows and column are equal
			{return 0;}

			virtual bool is_diagnol()//virtual function to check if the matrix is diagonal
			{return 0;}
			
			virtual bool is_symmetric()//virtual function to check if the matrix is symmetric(transpose of a matrix=matrix)
			{return 0;}

			virtual bool is_skew_symmetric()//virtual function to check if the matrix is skewsymmetric(transpose of matrix=negative of matrix)
			{return 0;}

			virtual special_functions take_adjoint()//virtual function to take adjoint of the matrix
			{
				special_functions temp(0,0);
				return temp;
			}


};


class adjoint:public special_functions{//class adjoint derived from base class special_functions

public:
	adjoint():special_functions()
	{}
	adjoint(const int r,const int c):special_functions(r,c)
	{}
	virtual ~adjoint()
	{}
	
	special_functions take_adjoint()//to take the adjoint of the given matrix
	{
		if(row_num!=col_num)//to check the poosibility to carry out the function
		{
			cout << "Adjoint of given matrix is not poosible :(" <<endl<<endl;
			special_functions temp1(0,0);
			return temp1;
		}
		else
		{
			special_functions temp2(row_num,col_num);//creating object of class special_functions 
			if(row_num==1)
			{
				temp2.mat[0][0]= mat[0][0];// adjoint of 1x1 matrix is equal to its only element
			}

			if(row_num==2)// adjoint of 2x2 matrix
			{
				temp2.mat[0][0]=mat[1][1];
				temp2.mat[0][1]=  (-1) * mat[0][1];
				temp2.mat[1][0]=  (-1) * mat[1][0];
				temp2.mat[1][1]= mat[0][0];

			}

			if(row_num>=3)  //for 3x3 or higher the adjoint is equal to the transpose of the cofactor matrix
			{
				
				temp2=take_cofactor_matrix();// finding the cofactor matrix of the given matrix
				temp2=temp2.set_transpose();// taking the transpose of the cofactor matrix 

			}
			return temp2; 
		}
		
	}
};


class inverse:public adjoint{// class inverse derived from the class adjoint
public:
	inverse():adjoint()
	{}
	inverse(const int r,const int c):adjoint(r,c)
	{}

	virtual ~inverse()
	{}
	inverse take_inverse()// for taking inverse of the matrix
	{
		
	    special_functions temp1(row_num,col_num);// creating  object of class special_functions
	    inverse temp2(row_num,col_num);
		if(temp1.row_num==temp1.col_num)// checking condition to take inverse
		{
			temp1=take_adjoint();
			float d=det();
			for(int i=0;i<row_num;i++)
				{
					for(int j=0;j<col_num;j++)
					{
						temp2.mat[i][j] =  temp1.mat[i][j] / d ;// inverse is equal to the adjoint of matrix divided by
					}											//its determinant
				}
			
			return temp2;
		}
		else
		{
			cout<<"Inverse of this two matrix is not possible.:("<<endl;
			inverse temp(0,0);
			return temp;
		}
	
	}
};
class types:public special_functions{//class types derived from the class special_functions 
public:
	types ():special_functions()
	{}
	types (const int r,const int c):special_functions(r,c)
	{}

	virtual ~types()
	{}

	virtual bool is_square()//virtual function to check if the number of rows and column are equal
	{
		if(row_num==col_num)
			return 1;
		else 
			return 0;
	}
	virtual bool is_diagnol()//virtual function to check if the matrix is diagonal 
	{
		if(row_num==col_num)
		{
			int c=0;
			int order=row_num;
			for(int i=0;i<order;i++)
			{				
				for(int j=0;j<order;j++)
				{
					if (i!=j)
					{
						if(mat[i][j]==0)//if all the elements except for the diagonal elements are zero
						c++;
					}
				}
			}
			if(c < (order*order)-order)//checking condition to return true or false
			return(0);
			else return 1;
		}
	}
	virtual bool is_symmetric()//virtual function to check if the matrix is symmetric(transpose of a matrix=matrix)
	{
		special_functions temp(row_num,col_num);
		temp=set_transpose();// to take transpose of the matrix

		if(row_num==col_num)
		{
			int c=0;
			int order=row_num;
			for(int i=0;i<order;i++)
			{
				for(int j=0;j<order;j++)
				{
					if(temp.mat[i][j]== mat[i][j])
					c++;
				}
			}
			if(c<(order*order))//checking condition to return true or false
				return 0;
			else
				return 1;
		}

	}
	virtual bool is_skew_symmetric()//virtual function to check if the matrix is skewsymmetric(transpose of matrix=negative of matrix)
	{
		special_functions temp(row_num,col_num);
		temp=set_transpose();// to take transpose of the matrix

		if(row_num==col_num)
		{
			int c=0;
			int order=row_num;
			for(int i=0;i<order;i++)
			{
				for(int j=0;j<order;j++)
				{
					if(temp.mat[i][j]== (-1)*mat[i][j])
					c++;
				}
			}
			if(c<(order*order))//checking condition to return true or false
				return 0;
			else
				return 1;
		}
	}
};



int main()
	{
		
		char c;
		int selection;
A:
		system("color 3F");//colour of the console 
		cout<<"WELCOME TO THE MATRIX CALCULATOR"<<endl;
		do{
		cout<<endl<<"You can perform following operations with your matrices:"<<endl<<endl<<"1.Addition\n2.Subtraction\n3.Multiplication\n4.Division by a scalar number\n5.Negative\n6.Trace\n7.Determinant\n8.Transpose\n9.Minor\n10.Cofactor \n11.Cofactor matrix\n12.Adjoint\n13.Inverse\n14.Check the type of matrix "<<endl;
		cout<<endl<<"Select one of the above operation by typing in the serial number mentioned above:";
		cin>>selection;
		system("cls");//clear screen
		switch(selection)
		{
			//addition
			case 1:
				{
					system("color 4D");//colour of the console
					cout<<"SUM"<<endl<<endl;
					cout<<"write the two matrices you want to add:"<<endl<<"MATRIX 1"<<endl;
					basic_functions a1,a2,a3;
					a1.setmatrix();//  to set matrix
					cout<<"MATRIX 2"<<endl;
					a2.setmatrix();//  to set matrix
					system("cls");//clear screen
					cout<<"A = "<<endl;
					a1.display();
					cout<<endl<<"B = "<<endl;
					a2.display();
					cout<<endl<<endl<<"FINDING SUM...:"<<endl<<endl;
					cout<<"A+B = "<<endl;
					a3=a1+a2;//addition 
					a3.display();//display sum
					
				}
				break;
			system("cls");//clear screen

			//subtraction
			case 2:
				{
					system("color 4E");//colour of the console
					cout<<"DIFFERENCE"<<endl<<endl;
					cout<<"write the two matrices you want to find difference:"<<endl<<"MATRIX 1"<<endl;
					basic_functions b1,b2,b3;
					b1.setmatrix();//  to set matrix
					cout<<"MATRIX 2"<<endl;
					b2.setmatrix();//  to set matrix
					system("cls");//clear screen
					cout<<"A = "<<endl;
					b1.display();
					cout<<endl<<"B = "<<endl;
					b2.display();
					cout<<endl<<endl<<"FINDING DIFFERENCE...:"<<endl<<endl;
					cout<<"A-B = "<<endl;
					b3=b1-b2;//difference
					b3.display();//display difference
				
				}
			break;
			system("cls");//clear screen

			//multiplication
			case 3:
				{
					system("color 5F");//colour of the console
					cout<<"PRODUCT"<<endl<<endl;
					cout<<"write the two matrices you want to find difference:"<<endl<<"MATRIX 1"<<endl;
					basic_functions l1,l2,l3;
					l1.setmatrix();//  to set matrix
					cout<<"MATRIX 2"<<endl;
					l2.setmatrix();//  to set matrix
					system("cls");//clear screen
					cout<<"A = "<<endl;
					l1.display();
					cout<<endl<<"B = "<<endl;
					l2.display();
					cout<<endl<<endl<<"FINDING PRODUCT...:"<<endl<<endl;
					cout<<"A x B = "<<endl;
					l3=l1*l2;//multiplication
					l3.display();//display multiplication
								
				}
			break;
			system("cls");//clear screen
			case 4:
				{
					
		            system("color 2F");//colour of the console
					cout<<"DIVISION"<<endl<<endl;
					int s;
					cout<<"write the matrix:"<<endl<<endl<<"MATRIX "<<endl;
					matrix *ptr1,*ptr2;//pointers of class basic_functions created
					ptr1=new basic_functions;
					ptr1->setmatrix();//  to set matrix
					cout<<"Write the scalar no:";
					cin>>s;
					system("cls");//clear screen
					cout<<"A = "<<endl;
					ptr1->display();
					cout<<"SCALAR MULTIPLE:"<<s<<endl<<endl;
					cout<<"FINDING DIVISION..."<<endl<<endl;
					ptr1->division_matrix(s);//to carry out division
					ptr1->display();//to display the resultant martix
					delete ptr1;
				}
			break;
			system("cls");//clear screen
			//negative
			case 5:
				{
					system("color 4D");//colour of the console
					cout<<"NEGATIVE"<<endl<<endl;
					cout<<"write the matrix:"<<endl<<endl<<"MATRIX"<<endl;
					matrix *ptr1;//pointer of class basic_functions created
					ptr1=new basic_functions;
					ptr1->setmatrix();//  to set matrix
					system ("cls");//clear screen
					cout << "A = " <<endl<<endl;
					ptr1->display();
					cout<<"FINDING NEGATIVE ..."<<endl<<endl;
					ptr1->negative_matrix();//taking the negative of matrix
					cout << "-A = " <<endl<<endl;
					ptr1->display();//to display the resultant matrix
					delete ptr1;
				}
			break;
			system("cls");//clear screen
			//trace
			case 6:
				{
					
					system("color 5F");//colour of the console
					cout<<"TRACE"<<endl;
					cout<<"write the matrix you want to find trace of:"<<endl<<endl<<"MATRIX "<<endl;
					matrix *ptr1;//pointer of class basic_functions created
					ptr1=new basic_functions;
					ptr1->setmatrix();//  to set matrix
					system ("cls");//clear screen
					cout << "A = "<< endl<<endl;
					ptr1->display();
					cout<<"FINDING TRACE..."<<endl<<endl;
					float trace;
					trace=ptr1->trace_matrix();// trace of the matrix being calculated
					cout<<"Trace of the given matrix A is : "<<trace<<endl;
					delete ptr1;
				}
			break;
			system("cls");//clear screen
			case 7:
				{
					system("color 9D");//colour of the console
					cout<<"DETERMINANT"<<endl;
					cout<<"write the matrix you want to find determinant of:"<<endl<<endl<<"MATRIX "<<endl;
					special_functions d1;
					d1.setmatrix();//  to set matrix
					system ("cls");//clear screen
					cout << "A = " <<endl<<endl;
					d1.display();
					cout<<"FINDING DETERMINANT..."<<endl<<endl;
					cout<<"Determinant of the given matrix A is : "<<d1.det()<<endl<<endl;//give out the determinant
				}
			break;
			system("cls");//clear screen
			//transpose
			case 8:
				{
					system("color 4D");//colour of the console
					cout<<"TRANSPOSE"<<endl<<endl;
					cout<<"write the matrix:"<<endl<<endl<<"MATRIX"<<endl;
					special_functions *ptr1;//pointer of class class special_functions created
					ptr1=new special_functions;
					ptr1->setmatrix();//  to set matrix
					system("cls");//clear screen
					cout << "A = " <<endl<<endl;
					ptr1->display();
					cout<<"FINDING TRANSPOSE..."<<endl<<endl;
                    cout << "TRANSPOSE OF A = " <<endl<<endl;
					special_functions t1=ptr1->set_transpose();//transpose taken
					t1.display();//resultant matrix displayed
				}
			break;
			system("cls");//clear screen
			//minor
			case 9:
				{
					system("color 7D");//colour of the console
					int row,col;
					cout<<"MINOR"<<endl<<endl;
					cout<<"write the matrix:"<<endl<<endl<<"MATRIX"<<endl;
					special_functions m1,m2;
					m1.setmatrix();//  to set matrix
					cout<<"write the indexes for taking minor"<<endl<<"row num:";
					cin>>row;
					cout<<endl<<"column number:";
					cin>>col;
					system("cls");//clear screen
					cout << "A = " <<endl<<endl;
					m1.display();
					cout<<"ROW OMITTED = "<<row<<endl;
					cout<<"COLUMN OMITTED = "<<col<<endl<<endl;
					cout<<"FINDING MINOR..."<<endl<<endl;
					cout << "MINOR OF A = " <<endl<<endl;
					m2=m1.take_minor(row,col);//minor taken
					m2.display();//minor matrix displayed


				}
			break;
			system("cls");//clear screen
			case 10:
				{
					system("color 9F");//colour of the console
					int row,col;
					cout<<"COFACTOR"<<endl<<endl;
					cout<<"write the matrix:"<<endl<<endl<<"MATRIX"<<endl;
					special_functions c1;
					c1.setmatrix();//  to set matrix
					cout<<"write the indexes for taking minor"<<endl<<"row num:";
					cin>>row;
					cout<<endl<<"column number:";
					cin>>col;
					system("cls");//clear screen
					cout << "A = " <<endl<<endl;
					c1.display();
					cout<<"ROW OMITTED = "<<row<<endl;
					cout<<"COLUMN OMITTED = "<<col<<endl<<endl;
					cout<<"FINDING COFACTOR..."<<endl<<endl;
					float c2=c1.take_cofactor(row,col);//taking cofactor 
					cout<<"Cofactor is : "<<c2<<endl;//displaying cofactor 


				}
			break;
			system("cls");//clear screen
			case 11:
				{
					system("color 5F");//colour of the console
					cout<<"COFACTOR MATRIX"<<endl<<endl;
					cout<<"write the matrix:"<<endl<<endl<<"MATRIX"<<endl;					
					special_functions co1,co2;
					co1.setmatrix();//  to set matrix
					system ("cls");//clear screen
					cout << "A = " <<endl<<endl;
					co1.display();
					cout<<"FINDING COFACTOR MATRIX..."<<endl<<endl;
					cout << "COFACTOR MATRIX OF A = " <<endl<<endl;
					co2=co1.take_cofactor_matrix();//taking cofactor matrix
					co2.display();//displaying cofactor matrix
				
				}
			break;
			system("cls");//clear screen
			case 12:
				{
                    system("color 9E"); //colour of the console
					cout<<"ADJOINT"<<endl<<endl;
					cout<<"write the matrix:"<<endl<<endl<<"MATRIX"<<endl;					
					special_functions  *a1;
					a1=new adjoint;
					a1->setmatrix();//  to set matrix
					system ("cls");//clear screen
					cout << "A = " <<endl<<endl;
					a1->display();
					special_functions a2;
					cout<<"FINDING ADJOINT..."<<endl<<endl;
					cout << "ADJOINT OF A = " <<endl;
					a2=a1->take_adjoint();// taking adjoint of the matrix
					a2.display();//displaying adjoint
				}
			break;
			system("cls");//clear screen
			case 13:
				{
					system("color 1E");//colour of the console
					cout<<"INVERSE"<<endl<<endl;
					cout<<"write the matrix:"<<endl<<endl<<"MATRIX"<<endl;					
					inverse i1,i2;
					i1.setmatrix();//  to set matrix
					system ("cls");//clear screen
					cout << "A = " <<endl<<endl;
					i1.display();
					cout<<"FINDING INVERSE OF MATRIX..."<<endl<<endl;
					cout << "INVERSE OF A = " <<endl<<endl;
					i2=i1.take_inverse();//taking inverse 
					i2.display();//displaying inverse
				
				}
			break;
			system("cls");//clear screen

			case 14:
				{
					system("color 4D");//colour of the console
					cout<<"TYPE"<<endl<<endl;
					cout<<"write the matrix:"<<endl<<endl<<"MATRIX"<<endl;
					special_functions *ptr1;
					ptr1=new types;
					ptr1->setmatrix();//  to set matrix
					system("cls");//clear screen
                    cout << "A = " <<endl<<endl;
					ptr1->display();
					cout<<"FINDING TYPE..."<<endl;
					//checking types of matrices //
					if(ptr1->is_square()== 1)
						cout<<"Matrix entered is a 'SQUARE' matrix"<<endl;
					else
						cout<<"Matrix entered is a 'RECTANGULAR' matrix"<<endl;
					if(ptr1->is_diagnol()== 1)
						cout<<"Matrix entered is a 'DIAGONAL' matrix"<<endl;
					else
						cout<<"Matrix entered is not a 'DIAGONAL' matrix"<<endl;	
					
					if(ptr1->is_symmetric()== 1)
						cout<<"Matrix entered is a 'SYMMETRIC' matrix"<<endl;
					else
						cout<<"Matrix entered is not a 'SYMMETRIC' matrix"<<endl;

					if(ptr1->is_skew_symmetric()== 1)
						cout<<"Matrix entered is a 'SKEW SYMMETRIC' matrix"<<endl;
					else
						cout<<"Matrix entered is not a 'SKEW SYMMETRIC' matrix"<<endl;
					
				

				}
			break;
			system("cls");//clear screen
			default:
				{

					/*while(selection < 1 || selection >14)
					{*/
						cout<<endl<<"Your selection is not correct.\nPlease try again:";
						goto A;
					//}
				}
		}
				
				
				cout<<endl<<endl<<"do you want to continue your calculations??  y/n"<<endl;
				cin>>c;
				system("cls");//clear screen
		}while (c!= 'n');

		return 0;
}