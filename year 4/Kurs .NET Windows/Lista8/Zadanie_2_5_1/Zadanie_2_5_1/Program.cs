using System;
using System.Data.OleDb;

namespace Zadanie_2_5_1
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            string connString = "Provider=Microsoft.ACE.OLEDB.12.0; Data Source=Studenci.xlsx; Extended Properties='Excel 8.0; HDR=Yes'";
            string queryString = "SELECT * FROM [Arkusz1$]";
            using (var connection = new OleDbConnection(connString))
            {
                OleDbCommand command = new OleDbCommand(queryString, connection);
                connection.Open(); 
                OleDbDataReader reader = command.ExecuteReader();
                while (reader.Read())
                {
                    string row = "";
                    for (int i = 0; i < reader.FieldCount; i++)
                        row += reader[i] + " ";
                    Console.WriteLine(row);
                }
                reader.Close();
            }
            Console.ReadKey();
        }
    }
}