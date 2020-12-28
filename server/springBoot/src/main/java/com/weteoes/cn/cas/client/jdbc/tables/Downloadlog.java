package com.weteoes.cn.cas.client.jdbc.tables;


public class Downloadlog {

  private String type;
  private long count;
  private java.sql.Timestamp date;


  public String getType() {
    return type;
  }

  public void setType(String type) {
    this.type = type;
  }


  public long getCount() {
    return count;
  }

  public void setCount(long count) {
    this.count = count;
  }


  public java.sql.Timestamp getDate() {
    return date;
  }

  public void setDate(java.sql.Timestamp date) {
    this.date = date;
  }

}
