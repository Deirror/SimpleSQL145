# SimpleSQL145Project

![images](https://github.com/user-attachments/assets/255483a8-bfad-4c0a-883a-a7eb3d8ab3e8)

Aim of project?
-

This project aims to demonstrate important concepts of the object-oriented programming - abstraction, encapsulation, inheritance, and polymorphism.

How does it work?
-

When starting the program, the user will need to enter a path to the folder where the database data files are located. The application will then enter dialog mode and allow execution of requests to the database. The database is stored in .ss145 format!

What about the field types?
-

There are currently four types:
| Type Name | Description |
|---|---|
| `Integer` | Represents signed integers, also positive and negative |
| `Real` | Rrepresents double-precision floating-point numbers |
| `Text` | Stores character strings or textual information. It can contain any text of any length, including letters, numbers, symbols, and spaces |
| `Null` | It is equal to empty field |

What operations can be found?
-

This project supports most of the basic SQL functions like *select from*, *alter table*, *where expressions*, *delete from* and many other.
| Operation | Description |
|---|---|
| `show tables` | This command shows the names of all existing tables in the given directory |
| `select {<field1, field2, ...>, *} from <table name>` | *select from* is used to retrieve specific data from a table in a database |
| `create table <table name> (<field name> <field type>, ...)` | *create table* is used to define a new table in a database. It specifies the table name, column names, their data types |
| `insert into <table name> (<field1, field2, ...>) values (<field1 value, field2 value, ...>),  ...` | *insert into* is used to add new rows of data into a table. It specifies the table name, the columns to populate, and the corresponding values to insert |
| `alter table <table name> add <field name> <field type>` | Using *alter table add*, you can add a new column to the table with a specified data type |
| `alter table <table name> drop column <field name>` | *alter table* can be used to remove a column from an existing table using *drop column* |
| `alter table <table name> rename column <field name> to <new field name>` | *alter table* with *rename column* is used to rename an existing column in a table. This allows you to update the column name while retaining its data and properties |
| `update test_table set <field name>=<new value>` | *update set* is used to modify existing records in a table |
| `{update set, delete from, select from, join on} where <expression condition> {or, and} ...`| *where* filter rows based on specified conditions. It is absolutely powerful when combined with *join on* |
| `<select statement> join <table name> on <field name>=<field name>` | *join on* is used to combine rows from two or more tables based on a related column. The ON keyword specifies the condition for joining the tables | 
 
