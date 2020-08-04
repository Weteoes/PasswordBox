var Weteoes = {
    // 配置
    config: {
        // 使用软件存储
        userSoftware: true,
    },
    // 连接软件
    software: {
        url: {
            get: "http://127.0.0.1:23340/operating/browser/get",
            create: "http://127.0.0.1:23340/operating/browser/create",
            del: "http://127.0.0.1:23340/operating/browser/del",
        },
        operating: {
            get (client, host) {
                let data = { Host: host };
                Weteoes.basic.axios(
                    Weteoes.software.url.get,
                    data,
                    (r) => {
                        let data = r.data;
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
            create (host, user, pass) {
                let data = { Host: host, User: user, Pass: pass };
                Weteoes.basic.axios(
                    Weteoes.software.url.create,
                    data,
                    (r) => {
                        let data = r.data;
                        if (data.Code == 0) {
                            log("create ok");
                        } else {
                            log("create error")
                        }
                    }, (e) => {
                        log(e);
                    });
            },
            del (host) {
                let data = { Host: host };
                Weteoes.basic.axios(
                    Weteoes.software.url.del,
                    data,
                    (r) => {
                        let data = r.data;
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
            get (client, host) {
                let a = localStorage.getItem(host);
                if (a == null) { return; }
                a = JSON.parse(a);
                let user = a.user, pass = a.pass;
                if (user != undefined && pass != undefined) {
                    // 如果有数据
                    client.postMessage({ api: "getUserPassbyUrl", "user": user, "pass": pass }, () => { })
                }
            },
            create (host) {
                localStorage.setItem(host, JSON.stringify(variable));
            },
        }
    },
    basic: {
        axios (url, data, success, error) {
            if (typeof success != "function") { success = () => { }; }
            if (typeof error != "function") { error = () => { }; }
            axios.get(url, {
                params: data
            }).then((r) => {
                success(r);
            }).catch((e) => {
                error(e);
            })
        }
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
            if (Weteoes.config.userSoftware) {
                Weteoes.software.operating.create(variable.Host, variable.User, variable.Pass);
            } else {
                Weteoes.localStorage.operating.create(variable.Host);
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

    function getUserPassbyUrl () {
        if (!isOptionsOn()) { return }
        if (Weteoes.config.userSoftware) {
            Weteoes.software.operating.get(client, variable.Host);
        } else {
            Weteoes.localStorage.operating.get(client, variable.Host);
        }
    }

    function saveUrl () {
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
    function pd_data () {
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
function ready () {
    if (Weteoes.config.userSoftware) {
        log("将使用软件存储,安全性高");
    } else {
        log("将使用插件存储,安全性较低");
    }
}

// 全局开关
function isOptionsOn () {
    let a = options_read("passwordBox_options_on")
    if (a === 'true') return true
    return false
}

// 自动保存开关
function isOptionsAutoSave () {
    let a = options_read("passwordBox_options_autosave")
    if (a === 'true') return true
    return false
}

function log (...msg) {
    console.log(...msg);
}

function options_read (key) {
    return window.localStorage.getItem(key);
}

ready()