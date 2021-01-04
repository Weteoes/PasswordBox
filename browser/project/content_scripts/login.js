addDocumentEvent();
// 保存全局变量
let variable = {
  RunTimeConnect: null, // socket长连接
  readyFunction: false, // 是否已经执行过
  browserLoginHost: 'passwordbox.weteoes.cn' // 浏览器解密获取session的Host地址
};

function log(...msg) {
  console.log(...msg);
}

function main() {
  let passInput = findPassInput();
  if (passInput == null) {
    //log("找不到用户登录框 code:1"); 
    return;
  }
  let userInput = findUserInput(passInput);
  if (userInput == null) {
    //log("找不到用户登录框 code:2"); 
    return;
  }
  // 如果有登录框
  variable.input = { userInput: userInput, passInput: passInput };
  readyFunction();
  // 添加事件
  addInputEvent(userInput, passInput);
}

// 只会执行一次
function readyFunction() {
  if (variable.readyFunction) {
    return;
  }
  log("Init");
  variable.readyFunction = true;
  // 连接background
  socketConnect();
  URL();
}

function socketConnect() {
  try {
    variable.RunTimeConnect = chrome.runtime.connect();
    variable.RunTimeConnect.onMessage.addListener(function (msg) {
      switch (msg.api) {
        // 判断是否有保存账户的网站
        case "getUserPassbyUrl":
          variable.input.userInput.focus()
          variable.input.userInput.value = msg.user;
          variable.input.userInput.dispatchEvent(new Event('input'));
          variable.input.passInput.focus()
          variable.input.passInput.value = msg.pass;
          variable.input.passInput.dispatchEvent(new Event('input'));
          break;
      }
    });
  } catch (e) {
    log(e);
  }
}

function addDocumentEvent() {
  document.body.onclick = main;
}

function addInputEvent(userInput, passInput) {
  function PostMessageUser(user) {
    if (variable.RunTimeConnect === null) { return; }
    variable.RunTimeConnect.postMessage({ api: "user", "user": user }, () => { })
  }
  function PostMessagePass(pass) {
    if (variable.RunTimeConnect === null) { return; }
    variable.RunTimeConnect.postMessage({ api: "pass", "pass": pass }, () => { })
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
    if (user === "") { return; }
    PostMessageUser(user);
  }
  passInput.oninput = () => {
    let pass = passInput.value;
    if (pass === "") { return; }
    PostMessagePass(pass);
  }
}

function findPassInput() {
  let passInputList = document.querySelectorAll("input[type=password]");
  // 有多个密码框的时候
  for (let i of passInputList) {
    if (i.style.display == "none") {
      // 如果是隐藏的话就跳过
      continue;
    }
    // 不是隐藏就返回
    return i;
  }
  return null;
}

function findUserInput(passInput) {

  // 通过类型获取
  const findByType = () => {
    let userInputType = "input[type=email]";
    let a = document.querySelectorAll(userInputType);
    if (a.length >= 1) {
      return find(userInputType, passInput);
    }
    return null;
  }

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

  // 通过密码框往上获取
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
        if (i.style.display == "none") {
          // 如果是隐藏的话就跳过
          continue;
        }
        // 不是隐藏就返回
        return i;
      }
    }
  }
  const result = findByList() || findByType() || findByPassInput();
  return result;
}

// 监听URL
function URL() {
  let lastURL = location.href;
  function A() {
    let nowURL = location.href;
    if (lastURL == nowURL) { return; }
    lastURL = nowURL;
    log("页面已经切换");
    main();
  }
  setInterval(A, 100);
}



readyBrowserAES()
/**
 * 浏览器解密
 */
// 初始化
function readyBrowserAES() {
  console.log('aes', location.host, variable.browserLoginHost, location.host === variable.browserLoginHost)
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
  chrome.cookies.get({ "url": variable.browserLoginHost, "name": 'w' }, function (cookie) {
    console.log(cookie)
  });
  return getCookie("w")
}



/**
 * Basic
 */
function getCookie(name) {
  var strcookie = document.cookie;//获取cookie字符串
  var arrcookie = strcookie.split("; ");//分割
  //遍历匹配
  for (var i = 0; i < arrcookie.length; i++) {
    var arr = arrcookie[i].split("=");
    if (arr[0] == name) {
      return arr[1];
    }
  }
  return "";
}