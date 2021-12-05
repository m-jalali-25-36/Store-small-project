#include <iostream>
#include "../class/UnitWorkDb.cpp"
#include "../tools/show.cpp"
#include "./selectCategory.cpp"
#include "./printProduct.cpp"

#pragma once
using namespace std;

void editProductPanel(UnitWorkDb *db, int editId)
{
    Product product = db->getProductDb()->GetById(editId);
    Category category = db->getCategoryDb()->GetById(product.getCategoryId());
    product.setCategoryName(category.getName());
    printProduct(&product);
    cout << "-------------------------------------" << endl;
    Product newProduct;
    string inp;
    cout << "Name> ";
    getline(cin, inp);
    if (inp != "")
        newProduct.setName(inp);
    int idCategory;
    selectCategory(db, &idCategory, &inp);
    printProduct(&product);
    cout << "Name> " << newProduct.getName() << endl;
    cout << "Category> " << inp << endl;
    if (idCategory != -1)
        newProduct.setCategoryId(idCategory);
    cout << "Price> ";
    getline(cin, inp);
    if (inp != "")
        newProduct.setPrice(toInt(inp));
    cout << "Quantity> ";
    getline(cin, inp);
    if (inp != "")
        newProduct.setQuantity(toInt(inp));
    cout << "Description> ";
    getline(cin, inp);
    if (inp != "")
        newProduct.setDescription(inp);
    newProduct.setId(product.getId());
    if (newProduct.getName() == "")
        newProduct.setName(product.getName());
    if (newProduct.getCategoryId() == -1)
        newProduct.setCategoryId(product.getCategoryId());
    if (newProduct.getPrice() == -1)
        newProduct.setPrice(product.getPrice());
    if (newProduct.getQuantity() == -1)
        newProduct.setQuantity(product.getQuantity());
    if (newProduct.getDescription() == "")
        newProduct.setDescription(product.getDescription());
    if (db->getProductDb()->Update(&newProduct))
        cout << "Product successfully edit." << endl;
    else
        cout << "Product edit failed!!!" << endl;
}
