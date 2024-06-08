/*********************************************************************************************************

This is to certify that this project is my own work, based on my personal efforts in studying 
and applying the concepts learned. I have constructed the functions and their respective algorithms 
and corresponding code by myself. The program was run, tested, and debugged by my own efforts. 
I further certify that I have not copied in part or whole or otherwise plagiarized the work of other 
students and/or persons.

Adriel Manuel Dimaano Fancubit, 12206547

*********************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef char string10[10]; // strings with 10 characters
typedef char string15[15]; // strings with 15 characters
typedef char string20[20]; // strings with 20 characters
typedef char string30[30]; // strings with 30 characters

struct PRODUCT
{
    int iproductID; // product ID of the product
    int iSellerid; // ID of the seller

    string20 citemName; // its name
    string15 ccategory; // its category
    string30 citemDes; //  item description
    int iquantity; // available quantity
    float fprice; // price of the product

    float ftotalsale; // total sales of that product
};

struct CART 
{
    string20 name; // name of the product
    int sellerID; // ID of the seller of the product
    int productID; // ID of the product

    int quantity; // quantity they wish to purchase
    float price; // price of the product
    float totalprice; // price * quantity
};

struct USER 
{

    // ** USER INFORMATION
    int iUserid; // userID of each user
    string10 cUserpass; // their password
    string30 cAddress; // their address
    int iContact; // their contact information
    string20 cName; // their name

    // ** as a seller
    struct PRODUCT item[20]; // list of items they sell
    float totalsale;

    // ** as a buyer
    struct CART cart[10]; // lists of items they wish to purchase
    float totalpurchase;
    int iNumcart; // number of items in their cart
};

struct TRANSACTION 
{
    int day; // day of the transaction
    int month; // month of the transaction
    int year; // year of the transaction
    int sellerID; // id of the seller
    int buyerID; // id of the buyer
    struct CART cart[5]; //  struct array of items purchased
    int numItems; // number of items purchased
    float totalamount; // total amount of the transaction
};

/* getString20 gets up to 20 character input and stores it in a string
@param string - character array initialized with 20 elements
Pre-condition: string can only have up to 20 characters, including the spaces
*/

void getString20(string20 string)
{
    char ch;
    int i = 0;
    char temp[20];
    do
	{
        if (i==0)
		    scanf(" %c", &ch);
        else
            scanf("%c", &ch);
		
		if(ch != '\n')
		{
			temp[i] = ch;
			i++;
			temp[i] = '\0';
		}
	}while (i < 100 && ch != '\n');

    strcpy(string,temp);
}

/* getString15 gets up to 15 character input and stores it in a string
@param string - character array initialized with 15 elements
Pre-condition: string can only have up to 15 characters, including the spaces
*/
void getString15(string15 string)
{
    char ch;
    int i = 0;
    char temp[15];
    do
	{
        if (i==0)
		    scanf(" %c", &ch);
        else
            scanf("%c", &ch);
		
		if(ch != '\n')
		{
			temp[i] = ch;
			i++;
			temp[i] = '\0';
		}
	}while (i < 100 && ch != '\n');

    strcpy(string,temp);
}

/* getString30 gets up to 30 character input and stores it in a string
@param string - character array initialized with 30 elements
Pre-condition: string can only have up to 30 characters, including the spaces
*/
void getString30(string30 string)
{
    char ch;
    int i = 0;
    char temp[30];
    do
	{
        if (i==0)
		    scanf(" %c", &ch);
        else
            scanf("%c", &ch);
		
		if(ch != '\n')
		{
			temp[i] = ch;
			i++;
			temp[i] = '\0';
		}
	}while (i < 100 && ch != '\n');

    strcpy(string,temp);
}

/* checkid returns of the index of either a product or a user, depending on the parameter mode
@param numUsers - number of users
@param *user - struct array of users
@param numUserid - the given user id
@param mode - 0 if userid index, 1 if productid index
@param numProductid - the given product id
@param *numItems - an array containing the number of items each user have
*/
int checkid (int numUsers, struct USER *user, int numUserid, int mode, int numProductid, int *numItems)
{
    int i;
    int checkerUser = -1; 
    int checkerProduct= -1; 
    
    for (i=0; i<numUsers;i++) // returns the index of the user id
    {
        if (numUserid==user[i].iUserid)
            checkerUser = i;
    }
    
    // if the mode is 1
    // it will first find the index of the user id
    
    if (mode == 1 && checkerUser != -1)
    {
        for (i=0; i<numItems[checkerUser];i++) // then returns the index of the product id
        {
            if (numProductid == user[checkerUser].item[i].iproductID)
                checkerProduct = i;
        } 
    }
        
    if (mode != 1)
    {
        if (checkerUser != -1)
            return checkerUser; // returns the index
        else 
            return -1; // return -1 if not found
    }
    else
     {
        if (checkerProduct != -1)
            return checkerProduct; // returns the index
        else 
            return -1; // return -1 if not found
    }
}

/* checkDate checks the dates in between the two inputted dates by the user and does specific functions depending on the given mode
@param *user - struct array of users
@param *transactions - struct array of transactions
@param numUsers - number of users
@param numTransactions - number of transactions
@param mode - 3 if getting total sales, 5 if getting the total amount purchased by each buyer, 0 if getting the total amount sold by each seller
@param *ifromday - gets the day of the 1st date
@param  *ifrommonth - gets the month of the 1st date
@param *ifromyear - gets the year of the 1st date
@param itoday - gets the day of the 2nd date
@param itomonth gets the month of the 2nd date
@param itoyear gets the day of the 2nd date
*/
void checkDate(struct USER *user, struct TRANSACTION *transaction, int numUsers, int numTransactions, int mode, float *iTotalSales, int *ifromday, int *ifrommonth, int *ifromyear, int *itoday, int *itomonth, int *itoyear)
{
    int i;
    // enter from date
    printf("Enter Date 1: ");
    scanf("%i %i %i", ifromday, ifrommonth, ifromyear);

    while( *ifromday < 1 || *ifromday > 31 ||  *ifrommonth < 1 || *ifrommonth > 12 ||  *ifromyear < 1000 || *ifromyear > 9999 )
    {
        printf("INVALID DATE !!\n");
        printf("Enter Date 1: ");
        scanf("%i %i %i", ifromday, ifrommonth, ifromyear);
    }

    // enter to date
    printf("Enter Date 2: ");
    scanf("%i %i %i", itoday, itomonth, itoyear);

    while( *itoday < 1 || *itoday > 31 ||  *itomonth < 1 || *itomonth > 12 ||  *itoyear < 1000 || *itoyear > 9999 )
    {
        printf("INVALID DATE !!\n");
        printf("Enter Date 1: ");
        scanf("%i %i %i", ifromday, ifrommonth, ifromyear);
    }

    for(i=0;i<numTransactions;i++)
    {
        if (transaction[i].year >= *ifromyear && transaction[i].year <= *itoyear)
        {
            if (*ifromyear == *itoyear )
            {
                if (transaction[i].month >= *ifrommonth && transaction[i].month <= *itomonth)
                {
                    if (*ifrommonth == *itomonth)
                    {
                        if (transaction[i].day >= *ifromday && transaction[i].month <= *itoday)
                        {
                            if (mode == 5)
                                user[checkid(numUsers,user, transaction[i].buyerID,0,0,0)].totalpurchase += transaction[i].totalamount;
                            else if (mode == 3)   
                                *iTotalSales += transaction[i].totalamount;
                            else
                                user[checkid(numUsers,user, transaction[i].sellerID,0,0,0)].totalsale += transaction[i].totalamount;
                        }
                    }
                    else
                    {
                        if (mode == 5)
                            user[checkid(numUsers,user, transaction[i].buyerID,0,0,0)].totalpurchase += transaction[i].totalamount;
                        else if (mode == 3)   
                            *iTotalSales += transaction[i].totalamount;
                        else
                            user[checkid(numUsers,user, transaction[i].sellerID,0,0,0)].totalsale += transaction[i].totalamount;
                    }
                }
            }
            else
            {
                if (mode == 5) // you get the buyers total purchase
                    user[checkid(numUsers,user, transaction[i].buyerID,0,0,0)].totalpurchase += transaction[i].totalamount;
                else if (mode == 3)   
                    *iTotalSales += transaction[i].totalamount;
                else // you get the seller's total sale
                    user[checkid(numUsers,user, transaction[i].sellerID,0,0,0)].totalsale += transaction[i].totalamount;
            }       
                
        }
    }
}

/* convertIDtoString gets an integer and converts it to a string by storing each digit to each element of the character array
@param stringID - array of characters, to which the converted digits will be stored
@param UserID - an integer that has the given id
*/
void convertIDtoString(int UserID, char *stringID)
{
    int i, j=0, digit;
    int counter = 0;
    int tempNum;
    tempNum = UserID;
    while(UserID != 0)
    {
        UserID /= 10;
        counter++;
    }

    for(i=counter-1;i>=0;i--)
    {
        digit = tempNum/(pow(10,i));
        stringID[j] = digit + '0';
        tempNum -= digit * (pow(10,i));
        j++;
    }
    stringID[j] = '\0';
    strcat(stringID,".bag.txt"); // gets the name of the binary file of the user's cart
}

/* checkcart checks if the given seller exists in the cart
@param *user - struct array of users
@param usercheck - index of the logged in user
@param ID - given seller ID or product ID
@param mode - 1 or 0
*/

int checkcart (struct USER *user, int usercheck, int ID, int mode)
{
    int i;
    int checker = -1;
    if (mode  == 1) // meaning we re checking if the seller id exists and return its index
    {
        for(i=0;i<user[usercheck].iNumcart;i++)
        {
            if (ID == user[usercheck].cart[i].sellerID)
                {
                    checker = i;
                    i = user[usercheck].iNumcart;
                }
        }
    }
    else // meaning we re checking if the seller id exists and return its index
    {
        for(i=0;i<user[usercheck].iNumcart;i++)
        {
            if (ID == user[usercheck].cart[i].productID)
                {
                    checker = i;
                    i = user[usercheck].iNumcart;
                }
        }
    }

    return checker;
}

/* registerUser registers the user into the system
@param *usertxt - string of the file
@param *iUseridN - variable to be used in storing the id of the user
@param cUserpassN - string variable to be used in storing the password of the user
@param  cNameN - string variable to be used in storing the name of the user
@param cAddressN - string variable to be used in storing the address of the user
@param *NcContact - variable to be used in storing the contact information of the user
@param *user - struct array of users
@param numUsers - number of users
*/
void registerUser (char *usertxt, int *iUseridN, string10 cUserpassN, string20 cNameN, string30 cAddressN, int *NcContact, struct USER *user, int numUsers)
{
    FILE *openUser;

    string10 cUserpassNverify;

    int passCheck = 0;
    int i = 0;
    int userCheck = 0;



    while(passCheck == 0)
    {
        // checks if the UserId already exists
        while(userCheck == 0)
        {
            printf("Enter UserId: ");
            scanf("%i", iUseridN);

            if (numUsers != 0)
            {
                userCheck = checkid (numUsers, user, *iUseridN, 0, 0, 0);
                if (userCheck >= 0)
                {
                    printf("The User ID already exists. Please try again.\n");
                    userCheck = 0;
                }
                else
                    userCheck = -1;
            }
            else
                userCheck = -1;
        }

        printf("Enter Name: ");
        getString20(cNameN);

        while(strlen(cNameN) > 20 )
        {
            printf("\n\nErr... You can only enter up to 20 characters.\n");
            printf("Enter Name: ");
            getString20(cNameN);
        }

        printf("Enter Address: ");
        getString30(cAddressN);

        while(strlen(cAddressN) > 30 )
        {
            printf("\n\nErr... You can only enter up to 30 characters.\n");
            printf("Enter Address: ");
            getString30(cAddressN);
        }

        printf("\nWARNING: Do not put spaces in between numbers. Putting spaces will crash the program\n");
        printf("Enter Contact Number: 09-");
        scanf(" %i", NcContact);

        printf("\nReminder: No spaces when entering new password..\n");
        printf("Enter New Password: ");
        scanf("%s", cUserpassN);

        while(strlen(cUserpassN) > 10 )
        {
            printf("\n\nErr... You can only enter up to 10 characters.\n");
            printf("Enter New Password: ");
            scanf("%s", cUserpassN);
        }

        printf("Re-enter New Password: ");
        scanf("%s", cUserpassNverify);

        if(strcmp(cUserpassN, cUserpassNverify) == 0)
        {
            passCheck++;
        }
        else
            printf("Password does not match. Please try again.");
        
    }

    // add the new user to the array
    user[numUsers].iUserid = *iUseridN;
    strcpy(user[numUsers].cUserpass,cUserpassN);
    strcpy(user[numUsers].cName,cNameN);
    strcpy(user[numUsers].cAddress,cAddressN);
    user[numUsers].iContact = *NcContact;

    // adds the new user to the file
    openUser = fopen(usertxt, "a");

    fprintf( openUser, "%i %s\n", user[numUsers].iUserid, user[numUsers].cUserpass);
    fprintf( openUser, "%s\n",user[numUsers].cName);
    fprintf( openUser, "%s\n", user[numUsers].cAddress);
    fprintf( openUser, "%i\n\n",  user[numUsers].iContact);

    

    fclose(openUser);

}

/* addItem adds new item into the system
@param *user - struct array of users
@param *numItems - an array containing the number of items each user have
@param iLogUserid - contains the id of the seller
@param usercheck - index of the logged in user
@param numUsers - number of users
*/

void addItem(struct USER *user, int *numItems, int iLogUserid, int usercheck, int numUsers)
{
    FILE *openItemsAdd; // adding the item to the Items.txt

    int iproductIDN;
    string20 citemNameN;
    string15 ccategoryN;
    string30 citemDesN;
    int iquantityN;
    float fpriceN;

    int i;
    int counter = 1;
    int checker = -1;

    openItemsAdd = fopen("Items.txt", "a");

    printf("-- Add New Item -- \n\n");
    printf("Enter Product ID: ");
    scanf("%i", &iproductIDN);
    
    while(checker == -1)
    {
        for(i=0;i<numUsers;i++)
        {
            // checks if the product id already exists
            checker = checkid(numUsers,user,user[i].iUserid,1,iproductIDN,numItems);
            if (checker > -1)
            {
                checker = 1; //  if its exists
                i = numUsers; //  ends the loop
            }
            
        }

        if (checker == 1) 
        {
            printf("Err... Product ID Already exists\n\n");
            printf("Enter Product ID: ");
            scanf("%i", &iproductIDN);
        }
        else
            checker = 0;

    }
    

    printf("Enter Item Name: ");
    getString20(citemNameN);

    while(strlen(citemNameN) > 20 )
        {
            printf("\n\nErr... You can only enter up to 20 characters.\n");
            printf("Enter Item Name: ");
            getString20(citemNameN);
        }

    printf("Enter Category: ");
    getString15(ccategoryN);

    while(strlen(ccategoryN) > 15 )
    {
        printf("\n\nErr... You can only enter up to 15 characters.\n");
        printf("Enter Category: ");
        getString15(ccategoryN);
    }


    printf("Enter Item Description: ");
    getString30(citemDesN);

    while(strlen(citemDesN) > 30 )
    {
        printf("\n\nErr... You can only enter up to 30 characters.\n");
        printf("Enter Category: ");
        getString15(citemDesN);
    }

    printf("Enter Quantity: ");
    scanf("%i", &iquantityN);

    printf("Enter Price: ");
    scanf(" %f", &fpriceN);


    // copies the entered information to the array
    user[usercheck].item[numItems[usercheck]].iproductID = iproductIDN;
    user[usercheck].item[numItems[usercheck]].iSellerid = iLogUserid; // who logged-in is the seller
    strcpy(user[usercheck].item[numItems[usercheck]].citemName,citemNameN);
    strcpy(user[usercheck].item[numItems[usercheck]].ccategory,ccategoryN); 
    strcpy(user[usercheck].item[numItems[usercheck]].citemDes,citemDesN);
    user[usercheck].item[numItems[usercheck]].iquantity = iquantityN;
    user[usercheck].item[numItems[usercheck]].fprice = fpriceN;

    
    // adds it to the Items.txt
    fprintf(openItemsAdd, "%i %i\n", user[usercheck].item[numItems[usercheck]].iproductID,  user[usercheck].item[numItems[usercheck]].iSellerid);
    fprintf(openItemsAdd, "%s\n", user[usercheck].item[numItems[usercheck]].citemName);
    fprintf(openItemsAdd, "%s\n", user[usercheck].item[numItems[usercheck]].ccategory);
    fprintf(openItemsAdd, "%s\n", user[usercheck].item[numItems[usercheck]].citemDes);
    fprintf(openItemsAdd, "%i %f\n\n", user[usercheck].item[numItems[usercheck]].iquantity, user[usercheck].item[numItems[usercheck]].fprice);

    fclose(openItemsAdd);
    numItems[usercheck]++; //  increments the number of items of the user

}

/* addTRANSACTION adds the trasaction.txt and prints the receipt
@param *user - struct array of users
@param usercheck - index of the logged in user
@param *transactions - struct array of transactions
@param *numTransactions - number of transactions
@param numUsers - number of users
@param iSpecificSellerID - seller in the transaction
@param day - day of the transaction
@param month - month of the transaction
@param year - year of the transaction
@param mode 1 if sellerid is given, 0 if the productid is given
@param productID - given productid
@param *numItems - an array containing the number of items each user have
*/

void addTRANSACTION(struct USER *user, int usercheck, struct TRANSACTION *transaction, int *numTransactions, int numUsers, int iSpecificSellerID, int day, int month, int year, int mode, int productID, int *numItems)
{
    int k = 0;
    int x = 0;
    int checker = 0;
    int i,j;

    transaction[*numTransactions].day = day;
    transaction[*numTransactions].month = month;
    transaction[*numTransactions].year = year;
    transaction[*numTransactions].buyerID = user[usercheck].iUserid;
    transaction[*numTransactions].totalamount = 0;
    // if the id is given
    if (mode == 1)
    {
        for (i=0;i<user[usercheck].iNumcart;i++)
        {
            if (user[usercheck].cart[i].sellerID == iSpecificSellerID)
            {
                transaction[*numTransactions].sellerID = user[usercheck].cart[i].sellerID;
                transaction[*numTransactions].cart[k] = user[usercheck].cart[i];
                transaction[*numTransactions].totalamount += user[usercheck].cart[i].totalprice;
                user[checkid(numUsers,user,transaction[*numTransactions].cart[k].sellerID,0,0,0)].item[checkid(numUsers,user,transaction[*numTransactions].cart[k].sellerID,1,transaction[*numTransactions].cart[k].productID, numItems)].iquantity -= transaction[*numTransactions].cart[k].quantity;
                k++;

                if (k == 5)
                {
                    checker = k;
                    i = user[usercheck].iNumcart;
                }
                    
            }
        }
        // remover

        for (i=0;i<user[usercheck].iNumcart;i++)
        {
            if (user[usercheck].cart[i].sellerID == iSpecificSellerID)
            {
                
                    for(j=i;j<user[usercheck].iNumcart-1;j++)
                    user[usercheck].cart[j] = user[usercheck].cart[j+1];
                checker --;
                i--;
                user[usercheck].iNumcart--;
                
                if (checker == 0)
                    i = user[usercheck].iNumcart;
                
            }
        }
        
        
    }
    else // if only the product id is given
    {
        // add the item to the transaction
        for (i=0;i<user[usercheck].iNumcart;i++)
        {
            if (user[usercheck].cart[i].productID == productID)
            {
                transaction[*numTransactions].sellerID = user[usercheck].cart[i].sellerID;
                transaction[*numTransactions].cart[k] = user[usercheck].cart[i];
                transaction[*numTransactions].totalamount += user[usercheck].cart[i].totalprice;
                user[checkid(numUsers,user,transaction[*numTransactions].cart[k].sellerID,0,0,0)].item[checkid(numUsers,user,transaction[*numTransactions].cart[k].sellerID,1,transaction[*numTransactions].cart[k].productID, numItems)].iquantity -= transaction[*numTransactions].cart[k].quantity;
                k++;
            }
        }

        for (i=0;i<user[usercheck].iNumcart;i++)
        {
            if (user[usercheck].cart[i].productID == productID)
            {
                for(j=i;j<user[usercheck].iNumcart-1;j++)
                    user[usercheck].cart[j] = user[usercheck].cart[j+1];
                
                user[usercheck].iNumcart--;
                i = user[usercheck].iNumcart;
            }
        }
    }

    printf("========================================== RECEIPT # %i ==========================================\n", (*numTransactions)+1);
    printf("Number of Items: %i\n", k);
    printf("==================================================================================================\n");
    printf("| Quantity   | Product ID   | Item Name              | Unit price   | Total Price               |\n");
    for(i=0;i<k;i++)
    {
        printf("| %10i |  %10i  |  %-20s", transaction[*numTransactions].cart[i].quantity, transaction[*numTransactions].cart[i].productID, transaction[*numTransactions].cart[i].name );
        printf("  |  %10.2f  |           %10.2f      |\n", transaction[*numTransactions].cart[i].price, transaction[*numTransactions].cart[i].totalprice);
    }

    printf("==================================================================================================\n");
    printf("Date: %i %i %i\n", transaction[*numTransactions].day, transaction[*numTransactions].month, transaction[*numTransactions].year);
    printf("Seller: %i | %s\n", transaction[*numTransactions].sellerID, user[checkid(numUsers, user, transaction[*numTransactions].sellerID,0,0,0)].cName);
    printf("Buyer: %i\n", transaction[*numTransactions].buyerID);
    printf("TOTAL AMOUNT: %.2f\n", transaction[*numTransactions].totalamount);
    printf("==================================================================================================\n\n");
    
    FILE *addTransact;
    addTransact = fopen("Transactions.txt", "a");
    transaction[*numTransactions].numItems = k; 
    fprintf(addTransact,"%i %i %i\n", transaction[*numTransactions].day, transaction[*numTransactions].month, transaction[*numTransactions].year);
    fprintf(addTransact,"%i\n", transaction[*numTransactions].sellerID);
    fprintf(addTransact,"%i\n", transaction[*numTransactions].buyerID);
    fprintf(addTransact,"%f\n", transaction[*numTransactions].totalamount);
    fprintf(addTransact,"%i\n", transaction[*numTransactions].numItems);
    for(i=0;i<k;i++)
    {
        fprintf(addTransact, "%i %i %i\n",transaction[*numTransactions].cart[i].productID, transaction[*numTransactions].cart[i].quantity, transaction[*numTransactions].cart[i].sellerID);
        fprintf(addTransact, "%s\n", transaction[*numTransactions].cart[i].name);
        fprintf(addTransact, "%.2f %.2f\n", transaction[*numTransactions].cart[i].price, transaction[*numTransactions].cart[i].totalprice);
    }
    fprintf(addTransact,"\n");
        
    fclose(addTransact);
    
    *numTransactions += 1;


}

/* sortItems sorts the item array of a user
@param mode - 1 if increasing sort, 2 if decresing sort
@param *user - struct array of users
@param index - given index of a user
@param temp - temporary USER structure to be used for the sorting algorithm
@param *numItems - an array containing the number of items each user have
*/
void sortItems (int mode, struct USER *user, int index, struct USER temp, int *numItems)
{
    int i = 0, counter = 0, x = 0;
    
    while(counter == 0)
    {

        for(i=0;i<numItems[index]-1;i++)
        {
            if (mode == 0) // decreasing
            {
                if (user[index].item[i+1].iproductID > user[index].item[i].iproductID)
                {
                    temp.item[0] = user[index].item[i];
                    user[index].item[i] = user[index].item[i+1];
                    user[index].item[i+1] = temp.item[0];
                    counter++;
                }  
            }

            else // increasing
            {
                if (user[index].item[i+1].iproductID < user[index].item[i].iproductID)
                {
                    temp.item[0] = user[index].item[i];
                    user[index].item[i] = user[index].item[i+1];
                    user[index].item[i+1] = temp.item[0];
                    counter++;
                }   
            }
              
        }

        if (counter > 0)
            counter = 0; 
        else   
            counter = 1;
    }
}

/* sortTopSellingItems sorts the product array of top selling items
@param *top_sellingProducts - struct array top selling items
@param nthItems - total number of items 
*/
void sortTopSellingItems(struct PRODUCT *top_sellingProducts, int nthItems)
{
    int i,j;
    int max;
    struct PRODUCT temp;

    for (i=0;i<nthItems-1;i++)
    {
        max = i;
        for(j=i+1;j<nthItems;j++)
        {
            // finds the max
            if (top_sellingProducts[max].ftotalsale < top_sellingProducts[j].ftotalsale)
                max = j;
        }

        if (max != i)
        {
            // swap the entire user id
            temp = top_sellingProducts[i];
            top_sellingProducts[i] = top_sellingProducts[max];
            top_sellingProducts[max] = temp;
        }
        
    }
}

/* sortCART sorts the cart array of a user
@param *user - struct array of users
@param usercheck - index of the logged in user
*/
void sortCART (struct USER *user, int usercheck)
{
    int i = 0, counter = 0, x = 0;
    struct USER temp;
    while(counter == 0)
    {

        for(i=0;i<user[usercheck].iNumcart;i++)
        {
    
            if (user[usercheck].cart[i+1].sellerID > user[usercheck].cart[i].sellerID)
            {
                temp.cart[0] = user[usercheck].cart[i]; 
                user[usercheck].cart[i] = user[usercheck].cart[i+1];
                user[usercheck].cart[i+1] = temp.cart[0];
                counter++;
            }  
        }

        if (counter > 0)
            counter = 0; 
        else   
            counter = 1;
    }
}

/* sortSellerID sorts the user based on their seller id
@param *user - struct array of users
@param numUsers - number of users
@param *numItems - an array containing the number of items each user have
*/
void sortSellerID(struct USER *user, int numUsers, int *numItems)
{
    int i,j;
    int min;
    struct USER temp;
    int tempo;
    for (i=0;i<numUsers-1;i++)
    {
        min = i;
        for(j=i+1;j<numUsers;j++)
        {
            // finds the min
            if (user[min].iUserid > user[j].iUserid)
                min = j;
        }

        if (min != i)
        {
            // swap the entire user id
            temp = user[i];
            user[i] = user[min];
            user[min] = temp;

            // swap the num items
            tempo = numItems[i];
            numItems[i] = numItems[min];
            numItems[min] = tempo;
        }
        
    }
}

/* checkQuantity checks if the supply is enough for the given quantity the user wants to add
@param *user - struct array of users
@param ProductID - given productid
@param quantity - quantity to be checked
@param numUsers - number of users
@param *numItems - an array containing the number of items each user have
*/
int checkQuantity(struct USER *user, int ProductID, int quantity, int numUsers, int *numItems)
{
    int i,j;
    int checker = 0;
    for(i=0;i<numUsers;i++)
    {
        for(j=0;j<numItems[i];j++)
        {
            if (ProductID == user[i].item[j].iproductID)
            {
                if ( quantity > user[i].item[j].iquantity)
                    checker = 1;

                i = numUsers;
                j = numItems[i];
            }
                
        }
    }
        
    return checker; 
}

/* checkPrice checks if the price changed
@param *user - struct array of users
@param SellerID - given seller id
@param ProductID - given product id
@param price - given price
@param numUsers - number of users
@param *numItems - an array containing the number of items each user have
@param *difference - calculates the difference between the price of the item, before and after the changes
*/
int checkPrice (struct USER *user, int SellerID, int ProductID, int price, int numUsers, int *numItems, float *difference)
{
    int i,j;
    int checker = 0;
    for(i=0;i<numUsers;i++)
        for(j=0;j<numItems[i];j++)
        {
            if (SellerID == user[i].iUserid && ProductID == user[i].item[j].iproductID && price != user[i].item[j].fprice)
            {
                checker = 1;
                i = numUsers;
                j = numItems[i];
                *difference = price - user[i].item[j].fprice;
            }
                
        }
    return checker;
}

/* textITEM loads the contents of the Items.txt to the system
@param *itemtxt - string of the Items.txt
@param *numItems - an array containing the number of items each user have
@param *user - struct array of users
@param numUsers - number of users
@param *nthItems - total number of items loaded
*/
void textITEM(char *itemtxt, int *numItems, struct USER *user, int numUsers, int *nthItems)
{
    int iIndexitem;
    int i;
    *nthItems = 0;
    int iProductcheck, iSellercheck;
    FILE *openItems; // opening the Items.txt
    // ----------------------------------------------
    // **scanning the Items.txt

    openItems = fopen(itemtxt, "r"); 

    if (openItems != NULL) 
    {
        for(i=0;i<100;i++) // initialize each num array to 0
            numItems[i] = 0;
        while(!feof(openItems))
        {
            fscanf(openItems, "%i %i\n", &iProductcheck, &iSellercheck);
            iIndexitem = checkid(numUsers,user, iSellercheck, 0, 0, 0); // finds the index of the seller of that particular product
            
            user[iIndexitem].item[numItems[iIndexitem]].iproductID = iProductcheck;
            user[iIndexitem].item[numItems[iIndexitem]].iSellerid = iSellercheck;
            fgets(user[iIndexitem].item[numItems[iIndexitem]].citemName, 20, openItems);
            user[iIndexitem].item[numItems[iIndexitem]].citemName[strlen(user[iIndexitem].item[numItems[iIndexitem]].citemName)-1] = '\0';
            
            fgets(user[iIndexitem].item[numItems[iIndexitem]].ccategory, 15, openItems);
            user[iIndexitem].item[numItems[iIndexitem]].ccategory[strlen(user[iIndexitem].item[numItems[iIndexitem]].ccategory)-1] = '\0';

            fgets(user[iIndexitem].item[numItems[iIndexitem]].citemDes, 30, openItems);
            user[iIndexitem].item[numItems[iIndexitem]].citemDes[strlen(user[iIndexitem].item[numItems[iIndexitem]].citemDes)-1] = '\0';

            fscanf(openItems, "%i %f\n\n", &user[iIndexitem].item[numItems[iIndexitem]].iquantity, &user[iIndexitem].item[numItems[iIndexitem]].fprice);
            numItems[iIndexitem]++;
            *nthItems += 1;
        }
               
    }
       
    fclose(openItems);
    // scanning stops**
    // ----------------------------------------------
}

/* textUSERS loads the contents of the User.txt to the system
@param *usertxt - string of the User.txt
@param *numItems - an array containing the number of items each user have
@param *user - struct array of users
@param numUsers - number of users
*/
void textUSERS(char *usertxt, int *numItems, struct USER *user, int *numUsers)
{
    FILE *openUser; // opening the User.txt
    int i,j;
    int tempid;
    string10 tempass;
    *numUsers = 0;
    // ----------------------------------------------
    // **scanning the User.txt
    openUser = fopen(usertxt, "r"); 

    if (openUser != NULL) 
    {
        while(!feof(openUser))
        {
            fscanf(openUser, "%i %s\n", &tempid, tempass);
            if (tempid != 0)
            {
                user[*numUsers].iUserid = tempid;
                strcpy(user[*numUsers].cUserpass, tempass);
                fgets(user[*numUsers].cName, 20, openUser);
                user[*numUsers].cName[strlen(user[*numUsers].cName)-1] = '\0';


                fgets(user[*numUsers].cAddress, 30, openUser);
                user[*numUsers].cAddress[strlen(user[*numUsers].cAddress)-1] = '\0';

                fscanf(openUser, "%i\n\n", &user[*numUsers].iContact);
                *numUsers += 1;
            }
            
        }
    }
    fclose(openUser);

    // scanning stops**
    // ----------------------------------------------
}

/* textUSERS loads the contents of the User.txt to the system
@param *user - struct array of users
@param usercheck - index of the logged in user
@param *stringID - string id of the logged in buyer
@param numUsers - number of users
*/

void textCART(struct USER *user, int usercheck, char *stringID, int numUsers)
{
    FILE *opencart;
    int tempid;
    int tempquantity;
    int tempsellerID;
    opencart = fopen(stringID, "r");
    user[usercheck].iNumcart = 0;
    if (opencart != NULL)
    {
        // reads the cart of the user
        while(!feof(opencart))
        {
        fscanf(opencart, "%i %i %i\n", &tempid, &tempquantity, &tempsellerID);
        if (checkid(numUsers,user,tempsellerID, 0,0,0) != -1)
        {
            user[usercheck].cart[user[usercheck].iNumcart].productID = tempid;
            user[usercheck].cart[user[usercheck].iNumcart].quantity = tempquantity;
            user[usercheck].cart[user[usercheck].iNumcart].sellerID = tempsellerID;
            fgets(user[usercheck].cart[user[usercheck].iNumcart].name, 20, opencart);
            user[usercheck].cart[user[usercheck].iNumcart].name[strlen(user[usercheck].cart[user[usercheck].iNumcart].name)-1] = '\0';
            fscanf(opencart, "%f %f\n\n", &user[usercheck].cart[user[usercheck].iNumcart].price, &user[usercheck].cart[user[usercheck].iNumcart].totalprice);

            user[usercheck].iNumcart++;
        }
        
        }
    }

     fclose (opencart);
}

/* textTRANSACTION loads the contents of the transaction.txt to the system
@param *user - struct array of users
@param *transaction - struct array of transactions
@param *numTransactions - number of transactions
*/
void textTRANSACTION(struct USER *user, struct TRANSACTION *transaction, int *numTransactions)
{
    FILE *opentransaction;
    *numTransactions = 0;
    int i;
    opentransaction = fopen("Transactions.txt", "r");

    if (opentransaction != NULL)
    {
        while(!feof(opentransaction))
        {

        transaction[*numTransactions].numItems = 0;
        fscanf(opentransaction,"%i %i %i\n", &transaction[*numTransactions].day, &transaction[*numTransactions].month, &transaction[*numTransactions].year);
        fscanf(opentransaction,"%i\n", &transaction[*numTransactions].sellerID);
        fscanf(opentransaction,"%i\n", &transaction[*numTransactions].buyerID);
        fscanf(opentransaction,"%f\n", &transaction[*numTransactions].totalamount);
        fscanf(opentransaction,"%i\n", &transaction[*numTransactions].numItems);

        for(i=0;i<transaction[*numTransactions].numItems;i++)
        {
            fscanf(opentransaction, "%i %i %i\n", &transaction[*numTransactions].cart[i].productID, &transaction[*numTransactions].cart[i].quantity, &transaction[*numTransactions].cart[i].sellerID );
            
            fgets(transaction[*numTransactions].cart[i].name , 20, opentransaction);
            transaction[*numTransactions].cart[i].name[strlen(transaction[*numTransactions].cart[i].name)-1] = '\0';

            fscanf(opentransaction, "%f %f\n\n", &transaction[*numTransactions].cart[i].price, &transaction[*numTransactions].cart[i].totalprice);
        }
        *numTransactions += 1;
        }
    }
    fclose (opentransaction);
}

/* textTOPSELLINGITEM loads the top selling items
@param *transaction - struct array of transactions
@param *numTransactions - number of transactions
@param nthItems - number of items
@param *top_sellingProducts - struct array of top selling products
*/

void textTOPSELLINGITEM(struct TRANSACTION *transaction, int numTransactions, int nthItems, struct PRODUCT *top_sellingProducts)
{
    FILE *openItems;
    int i,w,j;

    openItems = fopen("Items.txt", "r");

    for (i=0;i<nthItems;i++)
    { 
        fscanf(openItems, "%i %i\n", &top_sellingProducts[i].iproductID, &top_sellingProducts[i].iSellerid);

        fgets(top_sellingProducts[i].citemName, 20, openItems);
        top_sellingProducts[i].citemName[strlen(top_sellingProducts[i].citemName)-1] = '\0';
        
        fgets(top_sellingProducts[i].ccategory, 15, openItems);
        top_sellingProducts[i].ccategory[strlen(top_sellingProducts[i].ccategory)-1] = '\0';

        fgets(top_sellingProducts[i].citemDes, 30, openItems);
        top_sellingProducts[i].citemDes[strlen(top_sellingProducts[i].citemDes)-1] = '\0';

        fscanf(openItems, "%i %f\n\n", &top_sellingProducts[i].iquantity, &top_sellingProducts[i].fprice);

        
    }

    fclose(openItems);

    for (w=0;w<nthItems;w++)
    {
        top_sellingProducts[w].ftotalsale = 0;
        for (i=0;i<numTransactions;i++)
        {
            for (j=0;j<transaction[i].numItems;j++)
            {
                if (transaction[i].cart[j].productID == top_sellingProducts[w].iproductID)
                {
                    top_sellingProducts[w].ftotalsale += transaction[i].cart[j].totalprice;
                }
                
            } 
        }
    }
}

/* showCart prints the Cart of the user
@param *user - struct array of users
@param usercheck - index of the logged in user
*/
void showCart(struct USER *user, int usercheck)
{
    int i;
    if (user[usercheck].iNumcart == 0)
    {
        printf("Err... Your Cart is empty.");
    
    
    }
    else
    {
    printf("\n=======================================================================================================\n");
    printf("| Product ID  | Quantity     | Seller ID    | Name                   | Price        | Total Price     |\n");
    printf("=======================================================================================================\n");
    for(i=0;i<user[usercheck].iNumcart;i++)
    {
        printf("| %10i  |  ", user[usercheck].cart[i].productID);
        printf("%10i  |  ", user[usercheck].cart[i].quantity);
        printf("%10i  |  ", user[usercheck].cart[i].sellerID);
        user[usercheck].cart[i].name[strlen(user[usercheck].cart[i].name)] = '\0';
        printf("%-20s  |  ", user[usercheck].cart[i].name);
        printf("%10.2f  |  ", user[usercheck].cart[i].price);
        printf("%10.2f     |", user[usercheck].cart[i].totalprice);
        printf("\n");
    }
    }
    
}

/* showCart prints the Cart of the user
@param *user - struct array of users
@param *numItems - an array containing the number of items each user have
@param usercheck - index of the logged in user
*/
void showProducts(struct USER *user, int *numItems, int usercheck)
{
    int i;
    printf("\n=============================================================================================\n");
    printf(" Product ID |  Item name             |  Category              | Unit price   | Quantity     |\n");
    printf("=============================================================================================\n");
    for(i=0;i<numItems[usercheck];i++)
        {
        printf("%10i  |  ", user[usercheck].item[i].iproductID);
        printf("%-20s  |  ", user[usercheck].item[i].citemName);
        printf("%-20s  |  ", user[usercheck].item[i].ccategory);
        printf("%10.2f  |  ", user[usercheck].item[i].fprice);
        printf("%10i  |\n", user[usercheck].item[i].iquantity);
        }
}

/* rewriteCart rewrites the txt cart of the user
@param *stringID - string id of the logged in buyer
@param usercheck - index of the logged in user
@param *user - struct array of users
*/
void rewriteCart(char *stringID, int usercheck, struct USER *user)
{
    FILE *rewritecart; // opens cart for WRITING
    int i;
    rewritecart = fopen(stringID, "w");

    for(i=0;i<user[usercheck].iNumcart;i++)
        {
            fprintf(rewritecart, "%i %i %i\n", user[usercheck].cart[i].productID, user[usercheck].cart[i].quantity, user[usercheck].cart[i].sellerID);
            fprintf(rewritecart, "%s\n", user[usercheck].cart[i].name);
            fprintf(rewritecart, "%.2f %.2f\n", user[usercheck].cart[i].price, user[usercheck].cart[i].totalprice);

            if (i != user[usercheck].iNumcart - 1)
            {
                fprintf(rewritecart, "\n");
            }
        }
    fclose(rewritecart);
}

/* rewriteItem rewrites the Items.txt of the user
@param *stringID - string id of the logged in buyer
@param usercheck - index of the logged in user
@param *user - struct array of users
*/
void rewriteItem(char *itemtext, int numUsers, struct USER *user, int *numItems)
{
    FILE *openItem;
    int i,j;
    openItem = fopen(itemtext,"w");
    for (i=0;i<numUsers;i++)
    {
        for(j=0;j<numItems[i];j++)
        {
            fprintf(openItem, "%i %i\n", user[i].item[j].iproductID,  user[i].item[j].iSellerid);
            fprintf(openItem, "%s\n", user[i].item[j].citemName);
            fprintf(openItem, "%s\n", user[i].item[j].ccategory);
            fprintf(openItem, "%s\n", user[i].item[j].citemDes);
            fprintf(openItem, "%i %f\n\n", user[i].item[j].iquantity, user[i].item[j].fprice);
        }
    }

    fclose(openItem);
    
}

/* ewriteUser rewrites the User.txt
@param *usertext - string id of user.txt
@param numUsers - number of users
@param *user - struct array of users
*/
void rewriteUser(char *usertext, int numUsers, struct USER *user)
{
    FILE *openUser;
    int i;
    openUser = fopen(usertext,"w");
    for (i = 0;i<numUsers;i++)
    {
        fprintf( openUser, "%i %s\n", user[i].iUserid, user[i].cUserpass);
        fprintf( openUser, "%s\n",user[i].cName);
        fprintf( openUser, "%s\n", user[i].cAddress);
        fprintf( openUser, "%i\n\n",  user[i].iContact);
    }

    fclose(openUser);
}


int main ()
{
    struct USER user[100]; // user base
    struct USER utemp; // low stock (sell menu)
    struct TRANSACTION transaction[100]; // array of transactions
    struct PRODUCT top_sellingProducts[100]; // array of top selling products

    // for scanning // 
    int nthItems = 0; 
    int numItems[100]; 
    // ----------------------------------------------------

    // New User registration //
    char cregister;
    int iUseridN;
    string10 cUserpassN;
    string20 cNameN;
    string30 cAddressN;
    int iContactN;
    int numUserid;

    // ----------------------------------------------------

    // for the main program // 
    int imenu = 0; // for the menu
    int numUsers = 0; // number of users 
    int i, j, k, x = 0; // used in 'for' loops
 
    // ----------------------------------------------------

    // Logging in // 
    int iLogUserid; // the user id logging info
    string10 iLogUserpass; // the password logging info
    int usercheck; // returns the index of the user id
    int logincheck = -1; // checks if the password matches

    // ----------------------------------------------------


    // ============================================================================================================= 
    
    // USER MENU // 
    int iusermenu; // user menu options

    // ----------------------------------------------------

    // SELL MENU // 
    int isellmenu; 
    int ihowsort; // sends a int on how to sort the sent array (1 - increasing, 2 - decreasing)

        // edit stock
    int iproductIDedit;
    int iproductIndex = -1;

    int ieditsubmenu = 0;
    int ilowstockcounter = 0;
    char clowstockchar;

    string20 citemNameedit;
    string15 ccategoryedit;
    string30 citemDesedit;
    int iquantityedit;
    float fpriceedit;
    //---------------------------------------------------------------

    // BUY MENU //
    int ibuymenu = 0;
    char cshowseller = 'N';
    int iwhichsellerid;
    string15 cshowCategory; // 2.2.3
    int icategoryexists = 0; // 2.2.3
    char cshowsitemcategory; // 2.2.3
    string20 csearchitem; // 2.2.4
    int iitemmatch = 0;; // 2.2.4
    int rightsequence = 0; // 2.2.4
    char csearchitemnext; // 2.2.4
    char stringID[8]; //2.2.5
    int iCartchecker; // 2.2.5
    int isameItem = 0; // 2.2.5
    int ieditCartmenu = 0; // 2.2.6
    int iremCartSeller; // 2.2.6.1
    int iremCartSpe; // 2.2.6.2
    int iCarteditquan; // 2.2.6.3
    int newquan; // 2.2.6.3
    int isuccesseditquan = 0; // 2.2.6.3
    int iindexSeller; // 2.2.6.3

    int inewquantityindexSeller; // 2.2.6.3
    int inewquantityindexProduct; // 2.2.6.3
    int inewpriceindexSeller; // 2.2.6.3
    int inewpriceindexProduct; // 2.2.6.3
    int iquantitychangeindicator; // 2.2.6.3
    int ipricechangeindicator; // 2.2.6.3

    int icheckoutmenu; // 2.2.7
    int numTransactions = 0; // 2.2.7
    int iSpecificSellerID; // 2.2.7
    int day, month, year; // 2.2.7
    char proceedcheckout = 'N'; // 2.2.7
    int iSpecificProductID; // 2.2.7
    float difference; // 2.2.7

    //---------------------------------------------------------------

    // ADMIN MENU //

    int iadminmenu;
    int ifromday, ifrommonth,ifromyear;
    int itoday, itomonth,itoyear;
    float iTotalSales = 0;

    // ----------------------------------------------------------------

    // STATISTICS MENU

    int istatsmenu;
    FILE *openItems;

    // ---------------------------------------------------------------------


    FILE *writecart; // opens cart for APPENDING
    
    
while (imenu != 5) // does not stop until the user exits
{   
    // this loads the existing users, items, transactions and such for possible processing
    textUSERS("User.txt", numItems, user, &numUsers);
    textITEM("Items.txt", numItems, user, numUsers, &nthItems);
    textTRANSACTION(user, transaction, &numTransactions);
    textTOPSELLINGITEM(transaction, numTransactions, nthItems, top_sellingProducts);
    sortTopSellingItems(top_sellingProducts, nthItems);
    
    // welcome page
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> WELCOME to dstrct#4 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    printf("Where your wallet can either be a dIstrIct of income or a dIstrActION to your financial goals\n\n");
    
    printf("[1] Register as New User \n");
    printf("[2] User Menu \n");
    printf("[3] Admin Menu \n");
    printf("[4] Statistics \n");
    printf("[5] Exit \n");
    printf("Choose ::: "); 
    scanf("%i", &imenu);
        
    
    while(imenu > 5 || imenu < 1) // checks if the user inputs correctly
    {
        printf("\nInvalid... Please try again.\n");
        printf("[1] Register as New User \n");
        printf("[2] User Menu \n");
        printf("[3] Admin Menu \n");
        printf("[4] Statistics \n");
        printf("[5] Exit \n");
        printf("Choose: ");
        scanf("%i", &imenu);
    }


        if(imenu == 1)
        {
            registerUser ("User.txt", &iUseridN, cUserpassN, cNameN, cAddressN, &iContactN, user, numUsers);
            numUsers++; // increments the number of users
            imenu = 0;
        }
        else if (imenu == 2)
        {
            // the log in page
            printf("\n--LOG IN--\n");
            printf("\nWARNING: Please input the correct information. Doing otherwise\n");
            printf("may cause complications or error. Thank you for your understanding!\n\n");
            printf("User ID: ");
            scanf("%i",  &iLogUserid);
            printf("Password: ");
            scanf("%s",  iLogUserpass); // should not have space at it is a password

            usercheck = checkid (numUsers, user, iLogUserid, 0, 0, 0); // finds the index of the user that logged in
            
    
            if (strcmp(user[usercheck].cUserpass, iLogUserpass)==0)
                logincheck = 0; // if correct password

            if(logincheck == 0) // this means that logging info is in the array
            {
                printf("\nWelcome back! %s\n", user[usercheck].cName);
                user[usercheck].iNumcart = 0; // assumes that each user doesnt have annything in their cart
                iusermenu = 0; // resets the system

                while(iusermenu != 3)
                {
                    logincheck = -1; // immediately removes access after logging in

                    printf("\n[1] Sell Menu \n");
                    printf("[2] Buy Menu \n");
                    printf("[3] Exit User Menu\n");
                    printf("Choose: ");
                    scanf("%i", &iusermenu);

                    while(iusermenu < 1 || iusermenu > 3) // makes sure that input is correct
                    {
                        printf("Err... Please try again.\n\n");
                        printf("[1] Sell Menu \n");
                        printf("[2] Buy Menu \n");
                        printf("[3] Exit User Menu\n");
                        printf("Choose: ");
                        scanf("%i", &iusermenu);
                    }

                    if (iusermenu == 1)
                    {
                        // THIS IS THE SELL MENU
                        isellmenu = 0;
                        while(isellmenu != 5)
                        {
                            printf("\n\n== SELL MENU == \n");
                            printf("[1] Add New Item \n");
                            printf("[2] Edit Stock \n");
                            printf("[3] Show My Products \n");\
                            printf("[4] Show My Low Stock Products \n");
                            printf("[5] Exit Sell Menu \n");
                            printf("CHOOSE: ");
                            scanf("%i", &isellmenu);

                            while(isellmenu < 1 || isellmenu > 5) // makes sure the input is correct
                            {
                                printf("Err... Invalid Input\n\n");
                                printf("== SELL MENU == \n");
                                printf("[1] Add New Item \n");
                                printf("[2] Edit Stock \n");
                                printf("[3] Show My Products \n");\
                                printf("[4] Show My Low Stock Products \n");
                                printf("[5] Exit Sell Menu \n");
                                printf("CHOOSE: ");
                                scanf("%i", &isellmenu);
                            }

                            if (isellmenu == 1)
                            {
                                if (numItems[usercheck] < 20 )
                                {
                                    addItem(user, numItems,iLogUserid, usercheck,numUsers);
                                    isellmenu = 0;
                                }
                                else    
                                {
                                    printf("You can only sell up to 20 items.");
                                    isellmenu = 0;
                                }
                            }
                            else if(isellmenu == 2)
                            {
                                if (numItems[usercheck] > 0)
                                {
                                    ihowsort = 1; // increasing
                                    
                                    sortItems(ihowsort, user, usercheck, utemp, numItems);
                                    showProducts(user, numItems, usercheck);
                                    printf("\nEnter Product ID: ");
                                    scanf("%i", &iproductIDedit);

                                    // gets the index of the product
                                    iproductIndex = checkid(numUsers,user, user[usercheck].iUserid, 1, iproductIDedit, numItems);

                                    ieditsubmenu = 0; // rests the sub meu
                                    if (iproductIndex >= 0) // if the product is found
                                    {
                                        while(ieditsubmenu != 6)
                                        {
                                            printf("\n---- > Edit Stock <----\n\n");
                                            printf("++ OPTIONS ++ \n");
                                            printf("[1] Replenish \n");
                                            printf("[2] Change Price \n");
                                            printf("[3] Change Item name \n");
                                            printf("[4] Change Category \n");
                                            printf("[5] Change Description \n");
                                            printf("[6] Finish editing \n");
                                            printf("CHOOSE: ");
                                            scanf("%i", &ieditsubmenu);

                                            while(ieditsubmenu > 6 && ieditsubmenu < 1) // makes sure the input is valid
                                            {
                                                printf("Err... Invalid Input\n\n");
                                                printf("++ OPTIONS ++ \n\n");
                                                printf("[1] Replenish \n");
                                                printf("[2] Change Price \n");
                                                printf("[3] Change Item name \n");
                                                printf("[4] Change Category \n");
                                                printf("[5] Change Description \n");
                                                printf("[6] Finish editing \n");
                                                printf("CHOOSE: ");
                                                scanf("%i", &ieditsubmenu);
                                            }
                                            
                                            if (ieditsubmenu == 1)
                                            {
                                                printf("Enter quantity to be added: "); 
                                                scanf("%i", &iquantityedit);
                                                user[usercheck].item[iproductIndex].iquantity += iquantityedit;
                                                printf("Successfully Added !!");
                                            }
                                            else if (ieditsubmenu == 2)
                                            {
                                                printf("Enter new price: "); 
                                                scanf("%f", &fpriceedit);
                                                user[usercheck].item[iproductIndex].fprice = fpriceedit;
                                                printf("Successfully Edited !!");
                                            }
                                            else if (ieditsubmenu == 3)
                                            {
                                                printf("Enter new item name: "); 
                                                getString20(citemNameedit);

                                                while( strlen(citemNameedit) > 20)
                                                {
                                                    printf("\nErr... Please try again\n");
                                                    printf("Enter new item name: "); 
                                                    getString20(citemNameedit);
                                                }
                                                strcpy(user[usercheck].item[iproductIndex].citemName,citemNameedit);
                                                printf("Successfully Edited !!");
                                                
                                            }
                                            else if (ieditsubmenu == 4)
                                            {
                                                printf("Enter new category: "); 
                                                getString15( ccategoryedit);

                                                while( strlen(ccategoryedit) > 15)
                                                {
                                                    printf("\nErr... Please try again\n");
                                                    printf("Enter new category: "); 
                                                    getString15( ccategoryedit);
                                                }
                                                strcpy(user[usercheck].item[iproductIndex].ccategory,ccategoryedit);
                                                printf("Successfully Edited !!");
                                            }
                                            else if (ieditsubmenu == 5)
                                            {
                                                printf("Enter new description: "); 
                                                getString30(citemDesedit);
                                                
                                                while( strlen(citemDesedit) > 30)
                                                {
                                                    printf("\nErr... Please try again\n");
                                                    printf("Enter new description: "); 
                                                    getString30(citemDesedit);
                                                }
                                                strcpy(user[usercheck].item[iproductIndex].citemDes,citemDesedit);
                                                printf("Successfully Edited !!");
                                            }
                                            else
                                            {
                                                rewriteItem("Items.txt", numUsers, user, numItems);
                                                showProducts(user, numItems, usercheck);
                                                ieditsubmenu = 6;
                                            }

                                            
                                        }
                                    }
                                    else // if the product is not found
                                    {
                                        printf("Product ID does not exist.");
                                        isellmenu = 0;
                                    }
                                }
                                else
                                    printf("\nYou have no products to sell...\n");
                               
                                

                            }
                            else if(isellmenu == 3)
                            {
                                ihowsort = 1; // increasing
                                if (numItems[usercheck] > 0)
                                {
                                    printf("\n===================================== SHOWING PRODUCTS ======================================");
                                    sortItems(ihowsort, user, usercheck, utemp, numItems);
                                    showProducts(user, numItems, usercheck);
                                }
                                else
                                    printf("\nYou have no products to sell...\n");
                                
                            }
                            else if (isellmenu == 4)
                            {
                                ihowsort = 1; // increasing
                                ilowstockcounter = 0;
                                sortItems(ihowsort, user, usercheck, utemp, numItems);
                                if (numItems[usercheck] > 0)
                                {
                                    for(i=0;i<numItems[usercheck];i++)
                                    {
                                        if (user[usercheck].item[i].iquantity < 5)
                                        {
                                            utemp.item[ilowstockcounter] = user[usercheck].item[i];
                                            ilowstockcounter++;
                                        }
                                    }

                                    if (ilowstockcounter != 0)
                                    {
                                        printf("======================================================= LOW ON STOCK ============================================================");
                                        printf("\n=================================================================================================================================\n");
                                        printf(" Product ID |  Item name             |  Category              | Description                      | Unit price    | Quantity     |\n");
                                        printf("=================================================================================================================================\n");
                                        i = 0;
                                        while(i < ilowstockcounter)
                                        {
                                            printf("%10i  |  ", utemp.item[i].iproductID);
                                            printf("%-20s  |  ", utemp.item[i].citemName);
                                            printf("%-20s  |  ", utemp.item[i].ccategory);
                                            printf("%-30s  |  ", utemp.item[i].citemDes);
                                            printf(" %10.2f  |  ", utemp.item[i].fprice);
                                            printf("%10i  |\n", utemp.item[i].iquantity);

                                            printf("\nDo you wish to continue? (N/X): ");
                                            scanf(" %c", &clowstockchar);

                                            while (clowstockchar != 'X' && clowstockchar != 'N' )
                                            {
                                                printf("Err... Invalid Input\n");
                                                printf("\nDo you wish to continue? (N/X)");
                                                scanf(" %c", &clowstockchar);
                                            }
                                            
                                            if (clowstockchar == 'X')
                                                i = ilowstockcounter;
                                            else
                                            {
                                                printf("\n");
                                                i++;
                                            }
                                                

                                            if (i == ilowstockcounter)
                                                printf("That is all..\n");
                                        }
                                    }
                                    else
                                    {
                                        printf("\n No items are low on stock..");
                                    }
                                }
                                else
                                    printf("\nYou have no products to sell...\n");
                               
                                
                            }
                            else
                            {
                                isellmenu = 5;
                            }
                                
                        }  
                    }
                    else if (iusermenu == 2)
                    {
                        convertIDtoString(user[usercheck].iUserid, stringID); // gets the name of the txt cart file
                        
                        ibuymenu = 0;
                        while(ibuymenu!=8)
                        {
                            ibuymenu = 0;
                            textCART(user, usercheck, stringID, numUsers); 

                            printf("== BUY MENU == \n");
                            printf("[1] View all Products\n");
                            printf("[2] Show all Products by a Specific Seller\n");
                            printf("[3] Search Products by Category\n");
                            printf("[4] Search Products by Name\n");
                            printf("[5] Add to Cart\n");
                            printf("[6] Edit Cart\n");
                            printf("[7] Check Out Menu\n");
                            printf("[8] Exit Out Menu\n");
                            printf("CHOOSE: ");
                            scanf("%i", &ibuymenu);

                            while(ibuymenu > 8 || ibuymenu < 1) // makes sure the input is correct
                            {
                                printf("Err... Please try again.\n\n");
                                printf("== BUY MENU == \n");
                                printf("[1] View all Products\n");
                                printf("[2] Show all Products by a Specific Seller\n");
                                printf("[3] Search Products by Category\n");
                                printf("[4] Search Products by Name\n");
                                printf("[5] Add to Cart\n");
                                printf("[6] Edit Cart\n");
                                printf("[7] Check Out Menu\n");
                                printf("[8] Exit Out Menu\n");
                                printf("CHOOSE: ");
                                scanf("%i", &ibuymenu);
                            }
                            

                            if (ibuymenu == 1)
                            {
                                printf("-- View all Products -- \n\n");
                                sortSellerID(user, numUsers, numItems);
                                rewriteUser("User.txt", numUsers,user);
                                
                                usercheck = checkid (numUsers, user, iLogUserid, 0, 0, 0); // rechecks the index

                                for(i=0;i<numUsers;i++)
                                {
                                    printf("\nSELLER ID: %i\n", user[i].iUserid);
                                    showProducts(user, numItems, i);
                                    printf("\n");  

                                    if (i != numUsers-1 )
                                    {
                                        printf("\nNext? (N/X) ");
                                        scanf(" %c", &cshowseller);

                                        if (cshowseller != 'N' && cshowseller != 'X')
                                        {
                                            printf("\nErr... Invalid Input");
                                            printf("\nNext? (N/X) ");
                                            scanf(" %c", &cshowseller);
                                        }
                                    }
                                    else
                                    {
                                        printf("You have reached the END. \n\n");
                                    }
                                     
                                    if (cshowseller == 'X')
                                        i = numUsers; // ends the for loop
                                }
                            ibuymenu = 0;
                            }
                            else if(ibuymenu==2)
                            {
                                printf("Enter Seller ID: ");
                                scanf("%i", &iwhichsellerid);

                                if (iwhichsellerid == user[usercheck].iUserid)
                                {
                                    printf("\n >> Current showing your own products <<\n");
                                }
                    
                                showProducts(user, numItems, checkid(numUsers,user, iwhichsellerid, 0, 0, 0));
                                printf("\n");
                                ibuymenu = 0;
                            }
                            else if (ibuymenu==3)
                            {
                                printf("Enter Category: ");
                                scanf("%s", cshowCategory);

                                icategoryexists = 0; // resets the checker
                                for(i=0;i<numUsers;i++)
                                    for(j=0;j<numItems[i];j++)
                                    {
                                        if(strcmp(cshowCategory, user[i].item[j].ccategory) == 0)
                                            icategoryexists++;
                                    }

                                if (icategoryexists > 0)
                                {
                                    for(i=0;i<numUsers;i++)
                                    {
                                        for(j=0;j<numItems[i];j++)
                                        {   
                                            if(strcmp(cshowCategory, user[i].item[j].ccategory) == 0)
                                            {
                                                printf("%i", user[i].item[j].iproductID);
                                                printf("    %s", user[i].item[j].citemName);
                                                printf("    %s", user[i].item[j].ccategory);
                                                printf("    %f", user[i].item[j].fprice);
                                                printf("    %i\n", user[i].item[j].iquantity);

            
                                                printf("\nNext? (N/X) ");
                                                scanf(" %c", &cshowsitemcategory);

                                                while (cshowsitemcategory != 'N' && cshowsitemcategory != 'X')
                                                {
                                                    printf("\nErr... Invalid Input");
                                                    printf("\nNext? (N/X) ");
                                                    scanf(" %c", &cshowsitemcategory);
                                                }
                                               

                                            }

                                            if (cshowsitemcategory == 'X')
                                            {
                                                printf("That is all. \n");
                                                j = numItems[i];
                                                i = numUsers; // ends the for loop
                                            }
                                                
                                        }

                                        if (i == numUsers-1)
                                            printf("\nYou have reached the END. \n");
                                    }
                                    
                                }
                                else
                                    printf("The Category does not exist!\n");
                                ibuymenu = 0;
                            }
                            else if(ibuymenu==4)
                            {
                                printf("Search: ");
                                scanf("%s", csearchitem);

                                x = 0; // assumes that no user counts

                                for(i=0;i<numUsers;i++)
                                {
                                    // checks every item of the seller
                                    for(j=0;j<numItems[i];j++)
                                    {
                                        // checks every letter
                                        iitemmatch = 0;
                                        for(k=0;k < strlen(user[i].item[j].citemName);k++)
                                        {
                                            if (iitemmatch != strlen(csearchitem))
                                            {
                                                if (csearchitem[iitemmatch] == user[i].item[j].citemName[k])
                                                {
                                                rightsequence = 1; // rechecks the from start to finish, the word matches
                                                iitemmatch++;
                                                }
                                                else 
                                                {
                                                rightsequence = 0;
                                                }
                                            }
                                            else
                                            {
                                                k = strlen(user[i].item[j].citemName); // ends the 
                                            }
                                        }
                                        // if right sequence remains 1, it means that the word matches
                                        if (iitemmatch==strlen(csearchitem) && rightsequence == 1) // if the search word matches with any of the words in the product
                                            {
                                                printf("%i", user[i].item[j].iproductID);
                                                printf("    %s", user[i].item[j].citemName);
                                                printf("    %s", user[i].item[j].ccategory);
                                                printf("    %f", user[i].item[j].fprice);
                                                printf("    %i\n", user[i].item[j].iquantity);
                                                
                                                printf("\nNext? (N/X): ");
                                                scanf(" %c", &csearchitemnext);

                                                if (csearchitemnext == 'X')
                                                {
                                                    j = numItems[i];
                                                    i  = numUsers;
                                                }
                                            } 
                                    }
                                }  

                            if (rightsequence == 0)
                            {
                                printf("No item/s found...\n");
                            }
                            if (csearchitemnext == 'N')
                                printf("\nYou have each the END\n");

                            

                            
                            
                            ibuymenu = 0;     
                            }
                            else if (ibuymenu==5)
                            {
                                iCartchecker = 0;
                                
                                textTOPSELLINGITEM(transaction, numTransactions, nthItems, top_sellingProducts);
                                sortTopSellingItems(top_sellingProducts, nthItems);
                                if (numTransactions > 0 && nthItems >= 3)
                                {
                                    printf(" Here are some of the top selling products to date !\n");
                                    printf("\n============================================================\n");
                                    printf("|   Product ID    | Name                     | Total Sales |\n");
                                    printf("============================================================\n");
                                
                                for (i=0;i<3;i++)
                                    printf("| TOP <%i> %5i   | %-20s     | %10.2f  |\n", i+1, top_sellingProducts[i].iproductID,top_sellingProducts[i].citemName, top_sellingProducts[i].ftotalsale);
                                }
                                
                                    
                                if (user[usercheck].iNumcart < 10)
                                {
                                    printf("\nREMINDER: You cannot buy your own items \n\n");
                                    printf("Please enter the id of the product you wish to add...  \n");
                                while (iCartchecker != 1)
                                {
                                    printf("Product ID: ");
                                    scanf("%i", &user[usercheck].cart[user[usercheck].iNumcart].productID);
                                    printf("Quantity: ");
                                    scanf("%i", &user[usercheck].cart[user[usercheck].iNumcart].quantity);

                                    for(i=0;i<user[usercheck].iNumcart;i++)
                                        if (user[usercheck].cart[user[usercheck].iNumcart].productID == user[usercheck].cart[i].productID)
                                            {
                                                if (user[i].cart[i].quantity + user[usercheck].cart[user[usercheck].iNumcart].quantity < user[checkid(numUsers,user, user[usercheck].cart[i].sellerID,0,0,0)].item[checkid(numUsers,user, user[usercheck].cart[i].sellerID,1,user[usercheck].cart[i].productID,numItems)].iquantity)
                                                    {
                                                        printf("Adding the quantity since the item already exists\n");
                                                        user[usercheck].cart[i].quantity += user[usercheck].cart[user[usercheck].iNumcart].quantity;
                                                        isameItem = 1; // the item is already added to the cart
                                                        i = user[usercheck].iNumcart;
                                                        iCartchecker = 1;
                                                    }
                                                else
                                                    {
                                                        printf("While the item already exists, the quantity can't be added since the supply is not enough\n");
                                                        isameItem = 1; // the item is already added to the cart
                                                        i = user[usercheck].iNumcart;
                                                        iCartchecker = 1;
                                                    }
                                            }

                                    // checks all users
                                    if (isameItem == 0) // the item is new
                                    {
                                        for(i=0;i<numUsers;i++)
                                        {
                                            // checks every item of the seller
                                            for(j=0;j<numItems[i];j++)
                                            {
                                                // if found
                                                if (user[usercheck].cart[user[usercheck].iNumcart].productID == user[i].item[j].iproductID)
                                                {
                                    
                                                    if (user[i].item[j].iSellerid != user[usercheck].iUserid)
                                                    {
                                                        if (user[usercheck].cart[user[usercheck].iNumcart].quantity <= user[i].item[j].iquantity)
                                                        {
                                                            user[usercheck].cart[user[usercheck].iNumcart].sellerID = user[i].iUserid;
                                                            user[usercheck].cart[user[usercheck].iNumcart].price = user[i].item[j].fprice;
                                                            strcpy(user[usercheck].cart[user[usercheck].iNumcart].name, user[i].item[j].citemName);
                                                            user[usercheck].cart[user[usercheck].iNumcart].totalprice =  user[i].item[j].fprice * user[usercheck].cart[user[usercheck].iNumcart].quantity;
                                                            i = numUsers;
                                                            j = numItems[i];
                                                            iCartchecker = 1;
                                                        }
                                                        else
                                                        {
                                                            
                                                            iCartchecker = 2;
                                                            i = numUsers;
                                                            j = numItems[i];
                                                        }
                                                    }
                                                    else
                                                    {
                                                        iCartchecker = 3;
                                                        i = numUsers;
                                                        j = numItems[i];
                                                    }
                                                    
                                                }
                                            }
                                        }      
                                    }

                                    writecart = fopen(stringID, "a");

                                    if (iCartchecker == 0)
                                        printf("The items does not exist... \n");
                                    else if (iCartchecker == 2)
                                        printf("Insufficient Stock... \n");
                                    else if (iCartchecker == 3)
                                        printf("You cannot buy your own merchandise... \n");
                                    else if (isameItem == 0) // meaning the product ID is newly added to the cart
                                    {
                                        if (user[usercheck].iNumcart != 0)
                                        {
                                            fprintf(writecart, "\n");
                                        }

                                            fprintf(writecart, "%i %i %i\n", user[usercheck].cart[user[usercheck].iNumcart].productID, user[usercheck].cart[user[usercheck].iNumcart].quantity, user[usercheck].cart[user[usercheck].iNumcart].sellerID);
                                            fprintf(writecart, "%s\n", user[usercheck].cart[user[usercheck].iNumcart].name);
                                            fprintf(writecart, "%.2f %.2f\n", user[usercheck].cart[user[usercheck].iNumcart].price, user[usercheck].cart[user[usercheck].iNumcart].totalprice);
                                        
                                        user[usercheck].iNumcart++;
                                    }
                                }
                                }
                                else
                                {
                                    printf("Your cart reached maximum capacity. You can only have 10 items in your cart.\n");
                                    printf("\nYou may process to Edit Cart or Check out before adding more Items in you cart\n\n");
                                }
                                    

                                fclose(writecart);
                                rewriteCart(stringID, usercheck,user);
                            }
                            else if (ibuymenu==6)
                            {
                                if (user[usercheck].iNumcart <= 10 && user[usercheck].iNumcart > 0)
                                {
                                ieditCartmenu =0;
                                while(ieditCartmenu != 4)
                                {
                                    printf("\n------------------------------------------ Showing Cart ------------------------------------------\n");
                                    showCart(user,usercheck);
                                    printf("\n[1] Remove all items from Seller\n");
                                    printf("[2] Remove Specific Item\n");
                                    printf("[3] Edit Quantity\n");
                                    printf("[4] Finish Edit Cart\n");
                                    printf("CHOOSE: ");
                                    scanf("%i", &ieditCartmenu);

                                    while(ieditCartmenu > 4 && ieditCartmenu < 0) // makes sure the input is valid
                                    {
                                        printf("Err... Invalid Input\n");
                                        printf("\n[1] Remove all items from Seller\n");
                                        printf("[2] Remove Specific Item\n");
                                        printf("[3] Edit Quantity\n");
                                        printf("[4] Finish Edit Cart\n");
                                        printf("CHOOSE: ");
                                        scanf("%i", &ieditCartmenu);
                                    }

                                    if ( ieditCartmenu == 1)
                                    {
                                    printf("Please enter the Seller ID: ");
                                    scanf("%i", &iremCartSeller);

                                    while(checkcart(user,usercheck,iremCartSeller,1) == -1)
                                    {
                                        printf("\nSeller ID not found in cart\n");
                                        printf("Please enter the Seller ID: ");
                                        scanf("%i", &iremCartSeller);
                                    }

                                    for(i=0;i<user[usercheck].iNumcart;i++)
                                        {
                                        if (user[usercheck].cart[i].sellerID == iremCartSeller)
                                            {
                                                for(j=i ; j < user[usercheck].iNumcart-1;j++)
                                                {
                                                user[usercheck].cart[j].productID = user[usercheck].cart[j+1].productID;
                                                user[usercheck].cart[j].quantity = user[usercheck].cart[j+1].quantity;
                                                user[usercheck].cart[j].sellerID = user[usercheck].cart[j+1].sellerID;
                                                }
                                            i--;
                                            user[usercheck].iNumcart--;
                                            }
                                        }

                                    rewriteCart(stringID,usercheck,user);
                                    }
                                    else if (ieditCartmenu == 2)
                                    {
                                    printf("Please enter the Product ID of the product you wish to remove: ");
                                    scanf("%i", &iremCartSpe);

                                    while(checkcart(user,usercheck,iremCartSpe,0) == -1)
                                    {
                                        printf("\nProduct ID not found in cart\n");
                                        printf("Please enter the Product ID of the product you wish to remove: ");
                                        scanf("%i", &iremCartSpe);
                                    }
                                    
                                    for(i=0;i<user[usercheck].iNumcart;i++)
                                        {
                                        if (user[usercheck].cart[i].productID == iremCartSpe)
                                            {
                                                for(j=i ; j < user[usercheck].iNumcart-1;j++)
                                                {
                                                user[usercheck].cart[j].productID = user[usercheck].cart[j+1].productID;
                                                user[usercheck].cart[j].quantity = user[usercheck].cart[j+1].quantity;
                                                user[usercheck].cart[j].sellerID = user[usercheck].cart[j+1].sellerID;
                                                }
                                            i = user[usercheck].iNumcart;
                                            user[usercheck].iNumcart--;
                                                
                                            }
                                        }

                                    rewriteCart(stringID,usercheck,user);
                                    ieditCartmenu = 0;
                                    
                                    }
                                    else if(ieditCartmenu == 3)
                                    {
                                    isuccesseditquan = 0;
                                    while (isuccesseditquan != 1)
                                    {
                                    printf("Please enter the productID of the product you wish to edit: ");
                                    scanf("%i", &iCarteditquan);

                                    printf("Please enter new quantity: ");
                                    scanf("%i", &newquan);
                                    
                                    for(i=0;i <user[usercheck].iNumcart;i++)
                                        {
                                        if (user[usercheck].cart[i].productID == iCarteditquan)
                                            {
                                                iindexSeller = checkid(numUsers, user, user[usercheck].cart[i].sellerID, 0,0,0);
                                                if (checkQuantity(user, user[usercheck].cart[i].productID, newquan, numUsers, numItems) == 0)
                                                {
                                                    user[usercheck].cart[i].quantity = newquan;
                                                    user[usercheck].cart[i].totalprice = user[usercheck].cart[i].quantity * user[usercheck].cart[i].price;
                                                    i = user[usercheck].iNumcart;
                                                    isuccesseditquan = 1;
                                                }
                                                else
                                                {
                                                    i = user[usercheck].iNumcart;
                                                    isuccesseditquan = 2;
                                                }
                                            }
                                        }

                                    if (isuccesseditquan == 2)
                                        printf("Insufficient Stocks!!\n");
                                    else if (isuccesseditquan != 1)
                                        printf("Err... Item does not exist\n");

                                    }

                                    rewriteCart(stringID,usercheck,user);
                                    ieditCartmenu = 0;
                                    
                                    }
                                    else 
                                    {
                                        rewriteCart(stringID, usercheck, user);
                                        ieditCartmenu = 4;
                                    }
                                        

                                }
                                }
                                else
                                {
                                    printf("Err... Your Cart is empty\n\n");
                                }
                                
                                ibuymenu = 0;
                            }
                            else if (ibuymenu == 7)
                            {
                                
                            
                            iquantitychangeindicator = 0; // assumes that nothing has changed
                            ipricechangeindicator = 0; // assumes that nothing has changed
                            if (user[usercheck].iNumcart > 0 && user[usercheck].iNumcart <= 10)
                            {
                                icheckoutmenu = 0;
                                while(icheckoutmenu != 4 )
                                {   
                                    textCART(user, usercheck, stringID, numUsers);
                                    printf("--CHECK OUT MENU--\n");
                                    for(i=0;i<user[usercheck].iNumcart;i++)
                                    {
                                        // it will only print the changes if the chnages makes its supply
                                        // too insufficient for the buyer to buy it
                                        // it it detects changes, it will immediately change the quantity
                                        // in cart
                                        if (checkQuantity(user, user[usercheck].cart[i].productID, user[usercheck].cart[i].quantity, numUsers, numItems) == 1)
                                        {
                                        
                                            if (iquantitychangeindicator == 0)
                                                printf("ITEM QUANTITY CHANGES !!\n");

                                            printf("Item: %s", user[usercheck].cart[i].name );
                                            // finds the index of the seller
                                            inewquantityindexSeller = checkid(numUsers,user,user[usercheck].cart[i].sellerID,0,0,0);
                                            // finds the index of the product (in the seller)
                                            inewquantityindexProduct = checkid(numUsers,user,user[usercheck].cart[i].sellerID,1,user[usercheck].cart[i].productID, numItems); // finds the index of the product
                                            
                                            // after getting the seller and the product, print
                                            printf(" || Available Quantity:  %i", user[inewquantityindexSeller].item[inewquantityindexProduct].iquantity);
                                            printf(" << - Quantity in your cart:  %i\n", user[usercheck].cart[i].quantity);
                                            user[usercheck].cart[i].quantity = user[inewquantityindexSeller].item[inewquantityindexProduct].iquantity;
                                            user[usercheck].cart[i].totalprice = user[usercheck].cart[i].price * user[usercheck].cart[i].quantity;
                                            iquantitychangeindicator = 1;
                                        }
                                    }
                                    
                                    if (iquantitychangeindicator == 1)
                                        printf("\n");

                                    for(i=0;i<user[usercheck].iNumcart;i++)
                                    {
                                        if (checkPrice(user, user[usercheck].cart[i].sellerID, user[usercheck].cart[i].productID, user[usercheck].cart[i].price, numUsers, numItems, &difference) == 1)
                                        {
                                            
                                                if (ipricechangeindicator == 0)
                                                printf("ITEM PRICE POSSIBLE CHANGES !!\n");

                                                inewpriceindexSeller = checkid(numUsers,user,user[usercheck].cart[i].sellerID,0,0,0);
                                                inewpriceindexProduct = checkid(numUsers,user,user[usercheck].cart[i].sellerID,1,user[usercheck].cart[i].productID, numItems);
                                                printf("Item: %s", user[usercheck].cart[i].name );
                                                printf(" [PRICE BEFORE] :  %f ->>", user[inewpriceindexSeller].item[inewpriceindexProduct].fprice);
                                                printf(" [PRICE AFTER] : %f", user[usercheck].cart[i].price);
                                                printf(" || DIFFERENCE: %f\n", user[inewpriceindexSeller].item[inewpriceindexProduct].fprice - user[usercheck].cart[i].price);
                                                user[usercheck].cart[i].price = user[inewpriceindexSeller].item[inewpriceindexProduct].fprice;
                                                user[usercheck].cart[i].totalprice = user[usercheck].cart[i].price * user[usercheck].cart[i].quantity;
                                                
                                                ipricechangeindicator = 1;
                                        }
                                    }
                                    
                                if (iquantitychangeindicator == 1 || ipricechangeindicator == 1)
                                    printf("You may still change your cart !!\n");
                                

                                rewriteCart(stringID,usercheck,user);
                                icheckoutmenu = 0;

                                printf("Enter date: (day, month, year): ");
                                scanf("%i %i %i", &day, &month, &year);

                                while (day < 1 || day > 31 || month < 1 || month > 12 || year < 1 || year > 9999)
                                {
                                    printf("\nErr... Invalid date\n");
                                    printf("Enter date: (day, month, year): ");
                                    scanf("%i %i %i", &day, &month, &year);
                                }
                                
                                
                                printf("[1] All\n");
                                printf("[2] By a specific Seller\n");
                                printf("[3] Specific Item\n");
                                printf("[4] Exit Check out\n");
                                printf("CHOOSE: ");
                                scanf("%i",&icheckoutmenu);

                                while (icheckoutmenu < 1 || icheckoutmenu > 4)
                                {
                                    printf("Err... Invalid Input\n");
                                    printf("[1] All\n");
                                    printf("[2] By a specific Seller\n");
                                    printf("[3] Specific Item\n");
                                    printf("[4] Exit Check out\n");
                                    printf("CHOOSE: ");
                                    scanf("%i",&icheckoutmenu);
                                }

                                    if (icheckoutmenu == 1)
                                    {
                                        printf("You wish to Check out All\n");

                                        printf("Do you wish to proceed?: (Y/N) ");
                                        scanf(" %c", &proceedcheckout);

                                        while(proceedcheckout != 'N' && proceedcheckout != 'Y')
                                        {
                                            printf("Err... Invalid Input\n");
                                            printf("Do you wish to proceed? (Y/N): ");
                                            scanf(" %c", &proceedcheckout);
                                        }
                                        if (proceedcheckout == 'Y')
                                        {
                                            printf("Success!!\n");
                                            sortCART(user, usercheck);
                                            while(user[usercheck].iNumcart > 0)
                                                {
                                                    // adds the first id and finds products with the same seller ID
                                                    addTRANSACTION(user,usercheck,transaction, &numTransactions,numUsers,user[usercheck].cart[0].sellerID, day, month, year,1,0,numItems);
                                                    // rewrites the cart
                                                    rewriteCart(stringID,usercheck,user);
                                                    rewriteItem("Items.txt", numUsers,user, numItems);
                                                }
                                        }
                                        else
                                            icheckoutmenu = 0;

                                        ibuymenu = 0;
                                        icheckoutmenu = 4;
                                    
                                    }
                                    else if (icheckoutmenu == 2)
                                    {

                                        printf("Please enter Seller ID: ");
                                        scanf("%i", &iSpecificSellerID);

                                        while (checkcart (user, usercheck,iSpecificSellerID, 1) == -1)
                                        {
                                            printf("\nErr... Seller cannot be found\n");
                                            printf("Please enter Seller ID: ");
                                            scanf("%i", &iSpecificSellerID);
                                        }

                                        
                                        printf("Do you wish to proceed? (Y/N): ");
                                        scanf(" %c", &proceedcheckout);

                                        while(proceedcheckout != 'N' && proceedcheckout != 'Y')
                                        {
                                            printf("Err... Invalid Input\n");
                                            printf("Do you wish to proceed? (Y/N): ");
                                            scanf(" %c", &proceedcheckout);
                                        }

                                        if (proceedcheckout == 'Y')
                                        {
                                            // adds the first id and finds products with the same seller ID
                                            addTRANSACTION(user,usercheck,transaction, &numTransactions,numUsers,iSpecificSellerID,day, month, year, 1,0, numItems);
                                            // rewrites the cart
                                            rewriteCart(stringID, usercheck,user);
                                            rewriteItem("Items.txt", numUsers,user, numItems);
                                        }
                                        else
                                            icheckoutmenu = 0;

                                        icheckoutmenu = 4;
                                        ibuymenu = 0;
                                    }
                                    else if (icheckoutmenu == 3)
                                    {
                                        
                                        printf("Please enter Product ID: ");
                                        scanf("%i", &iSpecificProductID);

                                        while (checkcart (user, usercheck,iSpecificProductID, 0) == -1)
                                        {
                                            printf("\nErr... Product cannot be found\n");
                                            printf("Please enter Product ID: ");
                                            scanf("%i", &iSpecificProductID);
                                        }

                                        printf("Do you wish to proceed? (Y/N): ");
                                        scanf(" %c", &proceedcheckout);

                                        while(proceedcheckout != 'N' && proceedcheckout != 'Y')
                                        {
                                            printf("Err... Invalid Input\n");
                                            printf("Do you wish to proceed? (Y/N): ");
                                            scanf(" %c", &proceedcheckout);
                                        }

                                        if (proceedcheckout =='Y')
                                        {
                                            addTRANSACTION(user,usercheck,transaction, &numTransactions,numUsers,user[usercheck].cart[0].sellerID, day, month, year,0,iSpecificProductID, numItems);
                                            // rewrites the cart
                                            rewriteCart(stringID,usercheck,user);
                                            rewriteItem("Items.txt", numUsers,user, numItems);
                                        }
                                        else
                                            icheckoutmenu = 0;
                                        
                                        icheckoutmenu = 4;
                                        ibuymenu = 0;
                                        
                                    }
                                    else if (icheckoutmenu== 4)
                                    {
                                        icheckoutmenu = 4;
                                    }

                                }
                            }
                            else
                            {
                                printf("Err... Your Cart is empty\n");
                            }
                            
                            
                            ibuymenu = 0;

                            }
                            else 
                                ibuymenu = 8;
                        }
                    }
                    else
                        iusermenu = 3;   
                }
            }
            else
            {
                printf("User ID does not exist / Password is incorrect. \n\n");
                imenu = 0;
            }
        
        }
        else if (imenu == 3)
        {
            string10 cadminlogin;
            string10 cadminpassword = "momoney"; // admin password
            iadminmenu = 0;
            printf("Enter ADMIN Password: ");
            scanf("%s", cadminlogin);

            if (strcmp(cadminlogin,cadminpassword) == 0)
            {
                sortSellerID(user, numUsers,numItems);
                while(iadminmenu != 6)
                {
                iadminmenu = 0;
                printf("[1] Show all Users\n");
                printf("[2] Show all Sellers\n");
                printf("[3] Show Total Sales in Given Duration\n");
                printf("[4] Show Sellers Sales\n");
                printf("[5] Show Shopaholics\n");
                printf("[6] Back to Main Menu\n");
                printf("CHOOSE: ");
                scanf("%i", &iadminmenu);

                while (iadminmenu < 1 || iadminmenu > 6)
                {
                    printf("Err... Please try again.\n\n");
                    printf("[1] Show all Users\n");
                    printf("[2] Show all Sellers\n");
                    printf("[3] Show Total Sales in Given Duration\n");
                    printf("[4] Show Sellers Sales\n");
                    printf("[5] Show Shopaholics\n");
                    printf("[6] Back to Main Menu\n");
                    printf("CHOOSE: ");
                    scanf("%i", &iadminmenu);
                }
            
                if (iadminmenu == 1)
                {
                    if (numUsers > 0)
                    {
                    printf("\n===========================================================================================================\n");
                    printf("| User ID   | Password    | Name                  | Address                          | Contact Number     |\n");
                    printf("===========================================================================================================\n");
                            for(i=0;i<numUsers;i++)
                            {
                                printf("|%10i |", user[i].iUserid);
                                printf(" %-10s  | ", user[i].cUserpass);
                                printf("%-20s  |  ", user[i].cName);
                                printf("%-30s  |  ", user[i].cAddress);
                                printf("0 - %10i    |", user[i].iContact);
                                printf("\n");
                            }
                    }
                    else
                        printf("No Registered Users\n\n");
                }
                else if (iadminmenu == 2)
                {
                    printf("\n======================================================================================================================================\n");
                    printf("| User ID   | Password    | Name                  | Address                          | Contact Number     | Number of items for sale | \n");
                    printf("======================================================================================================================================\n");
                    if (numUsers > 0)
                    {
                        for(i=0;i<numUsers;i++)
                            if(numItems[i] > 0)
                            {
                                printf("|%10i |", user[i].iUserid);
                                printf(" %-10s  | ", user[i].cUserpass);
                                printf("%-20s  |  ", user[i].cName);
                                printf("%-30s  |  ", user[i].cAddress);
                                printf("0 - %10i    |", user[i].iContact);
                                printf("%22i    |", numItems[i]);
                                printf("\n");
                            }
                    }
                    else
                        printf("No Existing Sellers\n\n");
                }
                else if (iadminmenu == 3)
                {
                    if (numTransactions > 0)
                    {
                        iTotalSales = 0;
                        checkDate(user,transaction, numUsers, numTransactions, 3, &iTotalSales, &ifromday, &ifrommonth, &ifromyear, &itoday, &itomonth, &itoyear);
                        printf("Showing Total sales between %i %i %i and %i %i %i: %.2f\n", ifromday, ifrommonth, ifromyear, itoday, itomonth, itoyear, iTotalSales);
                    }
                    else
                        printf("No Existing Transactions \n");
                }
                else if (iadminmenu== 4)
                {
                    if (numUsers > 0)
                    {
                        for(i=0;i<numUsers;i++)
                            user[i].totalsale = 0;
                            
                        checkDate(user,transaction, numUsers, numTransactions, 4, 0, &ifromday, &ifrommonth, &ifromyear, &itoday, &itomonth, &itoyear);
                        
                        printf("\n================================================================\n");
                        printf("| Seller ID | Seller Name        | Total Sales in the duration |\n");
                        printf("================================================================\n");
                        
                        for(i=0;i<numUsers;i++)
                        {
                            if (user[i].totalsale > 0)
                            {
                                printf("| %-9i | %-18s | %-27.2f |",  user[i].iUserid, user[i].cName, user[i].totalsale);
                                printf("\n");
                            }
                                
                        }
                            
                    }
                    else
                        printf("No Existing Sellers\n\n");
                    
                        
                        
                        
                }
                else if (iadminmenu == 5)
                {
                    if (numUsers > 0)
                    {
                        for(i=0;i<numUsers;i++)
                        user[i].totalpurchase = 0;

                        checkDate(user,transaction, numUsers, numTransactions, 5, 0, &ifromday, &ifrommonth, &ifromyear, &itoday, &itomonth, &itoyear);
                        printf("\n============================= Shopaholics ==============================\n");
                        printf("\n========================================================================\n");
                        printf("| Buyer ID  | Buyer Name         | Total amount bought in the duration |\n");
                        printf("========================================================================\n");
                        
                        for(i=0;i<numUsers;i++)
                        {
                            if (user[i].totalpurchase > 0)
                            {
                                printf("| %-9i | %-18s | %-35.2f |",  user[i].iUserid, user[i].cName, user[i].totalpurchase);
                                printf("\n");
                            }
                                
                        }
                        printf("\n");
                    }
                    else
                        printf("No Existing Buyer\n\n");
                    
                }
                else 
                    iadminmenu = 6;
                }
            }
            else
            {
                printf("Unauthorized Access...");
                imenu = 0;
            }

            imenu = 0;
        }    
        else if (imenu == 4)
        {
            
            for (i=0;i<nthItems;i++)
                top_sellingProducts[i].ftotalsale = 0.00;

            while (istatsmenu != 2)
            {
                printf("-- Showing statistics -- \n");
                printf("[1] Top Selling Products\n");
                printf("[2] Exit Statistics\n");
                printf("Choose: ");
                scanf("%i", &istatsmenu);
                int a = 0;
                if (istatsmenu == 1)
                {
                    if (numTransactions > 0)
                    {
                        textTOPSELLINGITEM(transaction, numTransactions, nthItems, top_sellingProducts);
                        sortTopSellingItems(top_sellingProducts, nthItems);
                        printf("\n================ Top Selling Products ================\n");
                        printf("\n======================================================\n");
                        printf("| Product ID | Name                     | Total Sales |\n");
                        printf("======================================================\n");
                        for (i=0;i<nthItems;i++)
                        {
                            if (top_sellingProducts[i].ftotalsale > 0)
                            {
                                if (i == 0)
                                    printf("| TOP! %5i | %-20s     | %10.2f  |\n", top_sellingProducts[i].iproductID,top_sellingProducts[i].citemName, top_sellingProducts[i].ftotalsale);
                                else
                                    printf("| %10i | %-20s     | %10.2f  |\n", top_sellingProducts[i].iproductID,top_sellingProducts[i].citemName, top_sellingProducts[i].ftotalsale);
                            }
                            
                        }
                    }
                    else
                        printf("No recorded transactions\n");
                    

                    
                }
            }

        }
        else 
        {
            printf("\nThank you for using dstrct#4\n");
            printf("Good Bye !!");
        }
}
}






