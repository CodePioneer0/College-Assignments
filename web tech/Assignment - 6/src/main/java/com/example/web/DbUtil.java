package com.example.web;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;

public final class DbUtil {
  private static final String JDBC_URL = "jdbc:h2:./data/messages_db;AUTO_SERVER=TRUE";
  private static final String JDBC_USER = "sa";
  private static final String JDBC_PASS = "";

  private DbUtil() {}

  public static Connection getConnection() throws SQLException {
    return DriverManager.getConnection(JDBC_URL, JDBC_USER, JDBC_PASS);
  }

  public static void ensureSchema() throws SQLException {
    try (Connection conn = getConnection(); Statement st = conn.createStatement()) {
      st.execute("CREATE TABLE IF NOT EXISTS messages (" +
        "id IDENTITY PRIMARY KEY, " +
        "name VARCHAR(100) NOT NULL, " +
        "message VARCHAR(1000) NOT NULL, " +
        "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL)");
    }
  }
}




