(() => {
  // 全局变量
  let variable = {
    input: {
      userInput: null,
      passInput: null,
    },
    RunTimeConnect: null, // socket长连接
    readyFunction: false, // 是否已经执行过readyFunction函数
    browserLoginHost: 'passwordbox.weteoes.cn' // 浏览器解密获取session的Host地址
  };

  // 初始化
  ready()

  // 初始化函数
  function ready() {
    if (isIpv4()) {
      return
    }
    // readyBrowserAES()
    // 自动输入和点击页面自动输入(2种模式,可以兼容所有网页)
    readyInput()
    window.onclick = readyInput
  }
  // 初始化input
  function readyInput() {
    // 如果找到input,说明之前执行过，就退出
    if (variable.input.passInput != null) {
      return
    }
    // 寻找input
    let passInput = findPassInput();
    if (passInput == null) {
      // log("找不到用户登录框 code:1");
      return;
    }
    let userInput = findUserInput(passInput);
    if (userInput == null) {
      // log("找不到用户登录框 code:2");
      return;
    }
    // 如果有登录框
    variable.input = {
      userInput: userInput,
      passInput: passInput
    };
    readyFunction();
    // 添加事件
    addInputEvent(userInput, passInput);
  }
  // 初始化socket(只会执行一次)
  function readyFunction() {
    // 是否已经执行过
    if (variable.readyFunction) {
      return;
    }
    log("Init");
    variable.readyFunction = true;
    socketConnect(); // 连接socket
    addListenerURL(); // 监听URL
  }
  // 寻找input密码框
  // canDisplayNone 允许input的display属性为none
  function findPassInput(canDisplayNone = false) {
    let passInputList = document.querySelectorAll("input[type=password]");
    // 有多个密码框的时候
    for (let i of passInputList) {
      if (!canDisplayNone && i.style.display == "none") {
        // 如果是隐藏的话就跳过
        continue;
      }
      // 不是隐藏就返回
      return i;
    }
    // 如果input列表不为空,但找不到display不为none的，使用第一个none的input
    if (passInputList.length > 0) {
      return findPassInput(true)
    }
    return null;
  }
  // 通过input密码框向上寻找input用户输入框
  function findUserInput(passInput) {
    // 通过列表获取（优先级最高）
    const findByList = () => {
      const host = location.host // 获取Host
      let id = ""
      switch (host) {
        case "www.iqiyi.com":
          id = "[data-pwdloginbox=name]"
      }
      if (id) {
        return document.querySelector("input[type=text]" + id)
      }
      return null;
    }
    // 通过类型获取(input[type=email])
    const findByType = () => {
      let userInputType = "input[type=email]";
      let a = document.querySelectorAll(userInputType);
      if (a.length >= 1) {
        return find(userInputType, passInput);
      }
      return null;
    }
    // 通过密码框往上获取(input[type=text])
    const findByPassInput = () => {
      let userInputType = "input[type=text]";
      let a = document.querySelectorAll(userInputType);
      if (a.length >= 1) {
        return find(userInputType, passInput);
      }
      return null;
    }
    // 通过密码框往上获取
    const find = (userInputType, passInput) => {
      // 如果有2个input以上，包括2个
      let passInputParent = null;
      while (1) {
        if (passInputParent == null) {
          // 如果等于null，说明第一次寻找，等于passInput父级
          passInputParent = passInput.parentNode;
        } else {
          // 不然就是多次，等于passInputParent父级
          passInputParent = passInputParent.parentNode;
        }
        if (passInputParent == null) {
          // 说明网页已寻找完毕，找不到
          return null;
        }
        let userInputList = passInputParent.querySelectorAll(userInputType);
        // 如果有多个用户框的时候
        for (let i of userInputList) {
          if (i.style.display == "none" || i.hidden) {
            // 如果是隐藏的话就跳过
            continue;
          }
          // 不是隐藏就返回
          return i;
        }
      }
    }
    // 通过优先级获取
    const result = findByList() || findByType() || findByPassInput();
    return result;
  }
  // 判断HOST是否是ipv4地址
  function isIpv4() {
    return new RegExp("^[0-9]+.[0-9]+.[0-9]+.[0-9]+").test(location.host)
  }
  // 设置input框内容，兼容所有input
  function setInputValue(input, value) {
    input.focus()
    input.value = value
    input.dispatchEvent(new Event("input", {
      bubbles: !0,
      cancelable: !0
    }))
    input.dispatchEvent(new Event("change", {
      bubbles: !0,
      cancelable: !0
    }))
    setTimeout(() => {
      input.blur()
    }, 10)
  }
  // 监听input事件
  function addInputEvent(userInput, passInput) {
    function PostMessageUser(user) {
      if (variable.RunTimeConnect === null) {
        return;
      }
      variable.RunTimeConnect.postMessage({
        api: "user",
        "user": user
      }, () => {})
    }

    function PostMessagePass(pass) {
      if (variable.RunTimeConnect === null) {
        return;
      }
      variable.RunTimeConnect.postMessage({
        api: "pass",
        "pass": pass
      }, () => {})
    }
    let user = userInput.value;
    let pass = passInput.value;
    if (user != "") {
      PostMessageUser(user);
    }
    if (pass != "") {
      PostMessagePass(pass);
    }
    userInput.oninput = () => {
      let user = userInput.value;
      if (user === "") {
        return;
      }
      PostMessageUser(user);
    }
    passInput.oninput = () => {
      let pass = passInput.value;
      if (pass === "") {
        return;
      }
      PostMessagePass(pass);
    }
  }
  // 监听URL切换，不刷新页面内容，仅修改URL的情况(如：视频切换只刷新视频，修改URL地址)
  function addListenerURL() {
    let lastURL = location.href;

    function A() {
      let nowURL = location.href;
      if (lastURL == nowURL) {
        return;
      }
      lastURL = nowURL;
      readyInput();
    }
    setInterval(A, 100);
  }


  // 统一-日志
  function log(...msg) {
    console.log("[Password Box]", ...msg);
  }
  // 统一-连接socket
  function socketConnect() {
    try {
      variable.RunTimeConnect = chrome.runtime.connect();
      variable.RunTimeConnect.onMessage.addListener(function (msg) {
        switch (msg.api) {
          // 判断是否有保存账户的网站
          case "getUserPassbyUrl":
            setInputValue(variable.input.userInput, msg.user)
            setInputValue(variable.input.passInput, msg.pass)
            break;
        }
      });
    } catch (e) {
      log(e);
    }
  }


  /**
   * 浏览器解密
   */
  // 初始化
  function readyBrowserAES() {
    if (location.host === variable.browserLoginHost) {
      let w = getLoginSession()
      console.log("aaa", w)
      if (w) {
        console.log(w)
      }
    }
  }
  // 获取登录状态
  function getLoginSession() {
    chrome.cookies.get({
      "url": variable.browserLoginHost,
      "name": 'w'
    }, function (cookie) {
      console.log(cookie)
    });
    return getCookie("w")
  }


  /**
   * Basic
   */
  function getCookie(name) {
    var strcookie = document.cookie; //获取cookie字符串
    var arrcookie = strcookie.split("; "); //分割
    //遍历匹配
    for (var i = 0; i < arrcookie.length; i++) {
      var arr = arrcookie[i].split("=");
      if (arr[0] == name) {
        return arr[1];
      }
    }
    return "";
  }
})()