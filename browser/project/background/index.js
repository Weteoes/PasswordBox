var Weteoes = {
  // 配置
  config: {
    // 使用存储类型
    useType: 'software',
  },
  // 浏览器解密
  browser: {
    data: {
      config: '', // 配置，加密后
      configEmpty: false, // 配置是否为空，服务器
      aesP: '20000125', // 密码
      aesDecrypt: false, // 是否已经解密
      xmldom: null, // xml元素
      list: [] // 解密列表
    },
    url: {
      apiHost: 'http://127.0.0.1:8080',
      sooLogin: "https://cas.weteoes.cn/login?service=https%3A%2F%2Fpasswordbox.weteoes.cn%2Fsso%2Fredirect%3Furl%3Dhttps%253A%252F%252Fwww.weteoes.cn%252F",
      configGet: "/config/get", // apiHost + configGet
      configSet: "/config/set", // apiHost + configSet
    },
    operating: {
      // 尝试解密，并初始化
      aesPass(pass) {
        if (Weteoes.browser.data.configEmpty) {
          return false
        }
        // AES
        let config = Weteoes.browser.data.config
        if (config === '') {
          log('config empty')
          return false
        }
        var bytes = CryptoJS.AES.decrypt(config, pass);
        config = bytes.toString(CryptoJS.enc.Utf8);
        if (config === '') {
          log('aes pass error')
          return false
        }
        // operating
        var parser = new DOMParser();
        let xmldom = parser.parseFromString(config, 'text/xml');
        Weteoes.browser.data.xmldom = xmldom
        let queryList = xmldom.querySelectorAll("UserAndPassword")
        // 遍历加入
        let list = []
        for (let only of queryList) {
          let onlyList = {
            Host: only.getAttribute("Host"),
            User: only.getAttribute("User"),
            Pass: only.getAttribute("Pass")
          }
          list.push(onlyList)
        }
        Weteoes.browser.data.list = list
        Weteoes.browser.data.aesDecrypt = true
        Weteoes.browser.data.aesP = pass
        return true
      },
      // 服务器无配置，设置AES密码
      createAESPass(pass) {
        if (Weteoes.browser.data.configEmpty) {
          Weteoes.browser.data.aesP = pass
          Weteoes.browser.operating.setConfig()
          Weteoes.browser.data.configEmpty = false
          return true
        }
        return false
      },
      getConfig() {
        Weteoes.basic.axios(
          Weteoes.browser.url.configGet,
          {},
          (data) => {
            switch (data.code) {
              case 0:
                // 如果有配置文件
                let config = data.config
                Weteoes.browser.data.config = config
                return
              case 10:
                // 如果没有配置文件，创建一个，正常使用，在创建密码时会创建
                Weteoes.browser.data.configEmpty = true
                log('config empty')
                break
              default:
                log('getConfig error')
                return
            }
          }, (e) => {
            log(e);
          });
      },
      setConfig() {
        // 创建一个新的、文档元素为<root>的xml文档
        var xmldom = document.implementation.createDocument('', 'Weteoes', null)
        for (let i of Weteoes.browser.data.list) {
          let only = xmldom.createElement('UserAndPassword')
          only.setAttribute("Host", i.Host)
          only.setAttribute("User", i.User)
          only.setAttribute("Pass", i.Pass)
          xmldom.documentElement.appendChild(only)
        }
        let config = (new XMLSerializer()).serializeToString(xmldom)
        // AES
        config = CryptoJS.AES.encrypt(config, Weteoes.browser.data.aesP).toString();
        // operating
        Weteoes.basic.axios(
          Weteoes.browser.url.configSet,
          { config: config },
          (data) => {
            if (data.code !== 0) {
              log('setConfig error');
              return
            }
            // 成功
            Weteoes.browser.operating.getConfig()
          }, (e) => {
            log(e);
          }, 'post');
      },
      /**
       * 基础操作
       */
      del(host) {
        if (!Weteoes.browser.data.aesDecrypt) {
          return
        }
        for (let i = Weteoes.browser.data.list.length - 1; i > 0; i--) {
          if (Weteoes.browser.data.list[i].Host === host) {
            Weteoes.browser.data.list.splice(i, 1)
            break
          }
        }
        // 保存配置
        Weteoes.browser.operating.setConfig()
      },
      get(client, host) {
        if (!Weteoes.browser.data.aesDecrypt) {
          return
        }
        for (let i of Weteoes.browser.data.list) {
          if (i.Host === host) {
            client.postMessage({ api: "getUserPassbyUrl", "user": i.User, "pass": i.Pass }, () => { })
          }
        }
      },
      create(host, user, pass) {
        if (!Weteoes.browser.data.aesDecrypt) {
          return
        }
        let hasData = false
        for (let i of Weteoes.browser.data.list) {
          if (i.Host === host) {
            hasData = true
            i.User = user
            i.Pass = pass
          }
        }
        // 如果没有数据，添加
        if (!hasData) {
          let data = { Host: host, User: user, Pass: pass };
          Weteoes.browser.data.list.push(data)
        }
        // 保存配置
        Weteoes.browser.operating.setConfig()
      }
    },
  },
  // 连接软件
  software: {
    url: {
      get: "http://127.0.0.1:23340/operating/browser/get",
      create: "http://127.0.0.1:23340/operating/browser/create",
      del: "http://127.0.0.1:23340/operating/browser/del",
    },
    operating: {
      get(client, host) {
        let data = { Host: host };
        Weteoes.basic.axios(
          Weteoes.software.url.get,
          data,
          (data) => {
            if (data.Code == 0) {
              client.postMessage({ api: "getUserPassbyUrl", "user": data.Data.User, "pass": data.Data.Pass }, () => { })
              log("get ok");
            } else {
              log("get error")
            }
          }, (e) => {
            log(e);
          });
      },
      create(host, user, pass) {
        let data = { Host: host, User: user, Pass: pass };
        Weteoes.basic.axios(
          Weteoes.software.url.create,
          data,
          (data) => {
            if (data.Code == 0) {
              log("create ok");
            } else {
              log("create error")
            }
          }, (e) => {
            log(e);
          });
      },
      del(host) {
        let data = { Host: host };
        Weteoes.basic.axios(
          Weteoes.software.url.del,
          data,
          (data) => {
            if (data.Code == 0) {
              log("del ok");
            } else {
              log("del error");
            }
          }, (e) => {
            log(e);
          });
      },
    }
  },
  // 本地操作
  localStorage: {
    operating: {
      get(client, host) {
        let a = localStorage.getItem(host);
        if (a == null) { return; }
        a = JSON.parse(a);
        let user = a.user, pass = a.pass;
        if (user != undefined && pass != undefined) {
          // 如果有数据
          client.postMessage({ api: "getUserPassbyUrl", "user": user, "pass": pass }, () => { })
        }
      },
      create(host) {
        localStorage.setItem(host, JSON.stringify(variable));
      },
    }
  },
  basic: {
    axios(url, data, success, error, type = 'get') {
      if (typeof success != "function") { success = () => { }; }
      if (typeof error != "function") { error = () => { }; }
      switch (type) {
        case 'get':
          axios.get(url, {
            params: data
          }).then((r) => {
            success(r);
          }).catch((e) => {
            error(e);
          })
          break
        case 'post':
          axios.post(url,
            data
          ).then((r) => {
            success(r);
          }).catch((e) => {
            error(e);
          })
          break
      }
    },
  }
};

chrome.runtime.onConnect.addListener(function (client) {
  // 全局变量
  let variable = {};
  // 保存访问URL
  saveUrl();
  log(variable.Host, "connect");
  // 获取账户信息
  getUserPassbyUrl();

  client.onDisconnect.addListener(function () {
    if (!isOptionsOn()) { return }
    if (!isOptionsAutoSave()) { return }
    log(variable.Host, "disconnect");
    if (pd_data()) {
      switch (Weteoes.config.useType) {
        case "browser":
          break
        case "software":
          Weteoes.software.operating.create(variable.Host, variable.User, variable.Pass);
          break
        case "localStorage":
          Weteoes.localStorage.operating.create(variable.Host);
          break
      }
    } else {
      log(variable, "数据不合格")
    }
  });

  client.onMessage.addListener(function (msg) {
    if (!isOptionsOn()) { return }
    switch (msg.api) {
      // 用户名提交api
      case "user":
        variable.User = msg.user;
        break;

      // 密码提交api
      case "pass":
        variable.Pass = msg.pass;
        break;
    }
  });

  function getUserPassbyUrl() {
    if (!isOptionsOn()) { return }
    switch (Weteoes.config.useType) {
      case "browser":
        break
      case "software":
        Weteoes.software.operating.get(client, variable.Host);
        break
      case "localStorage":
        Weteoes.localStorage.operating.get(client, variable.Host);
        break
    }
  }

  function saveUrl() {
    let url;
    if (typeof client.sender.origin != "undefined") {
      // 如果有origin了话使用
      url = client.sender.origin;
    } else {
      // 个别浏览器没有origin需要自己处理
      let a = client.sender.url;
      let b = a.substr(0, a.indexOf("/", 8));
      url = b;
    }
    variable.Host = url;
  }

  // 判断数据是否有效
  function pd_data() {
    if (
      typeof variable.Host != "undefined" &&
      typeof variable.User != "undefined" &&
      typeof variable.Pass != "undefined"
    ) {
      return true;
    }
    return false;
  }
});
function ready() {
  switch (Weteoes.config.useType) {
    case "browser":
      log("将使用插件云存储,安全性较高");
      let a = Weteoes.browser.url
      a.configGet = a.apiHost + a.configGet
      a.configSet = a.apiHost + a.configSet
      break
    case "software":
      log("将使用软件存储,安全性中等");
      break
    case "localStorage":
      log("将使用插件本地存储,安全性较低");
      break
  }
  Weteoes.browser.operating.getConfig()
}

function readyAxios() {
  axios.interceptors.response.use((response) => {
    switch (response.data.code) {
      case 100:
        // 未登录
        switch (Weteoes.config.useType) {
          case 'browser':
            chrome.tabs.create({ url: Weteoes.browser.url.sooLogin })
            break
        }
        return response.data
      default:
        return response.data
    }
  })
}

// 全局开关
function isOptionsOn() {
  let a = options_read("passwordBox_options_on")
  if (a === 'true') return true
  return false
}

// 自动保存开关
function isOptionsAutoSave() {
  let a = options_read("passwordBox_options_autosave")
  if (a === 'true') return true
  return false
}

function log(...msg) {
  console.log(...msg);
}

function options_read(key) {
  return window.localStorage.getItem(key);
}

readyAxios()
ready()