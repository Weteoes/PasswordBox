package com.weteoes.cn.cas.client.jdbc.tables;


public class Session {

  private String session;
  private String uid;
  private java.sql.Timestamp createTime;


  public String getSession() {
    return session;
  }

  public void setSession(String session) {
    this.session = session;
  }


  public String getUid() {
    return uid;
  }

  public void setUid(String uid) {
    this.uid = uid;
  }


  public java.sql.Timestamp getCreateTime() {
    return createTime;
  }

  public void setCreateTime(java.sql.Timestamp createTime) {
    this.createTime = createTime;
  }

}
