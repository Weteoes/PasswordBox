chrome.runtime.onConnect.addListener(function (client) {
    // 全局变量
    let variable = {};
    // 保存访问URL
    saveUrl();
    log(variable.url, "connect");
    // 获取账户信息
    getUserPassbyUrl();

    function getUserPassbyUrl() {
        let a = localStorage.getItem(variable.url);
        if (a == null) { return; }
        a = JSON.parse(a);
        let user = a.user, pass = a.pass;
        if (user != undefined && pass != undefined) {
            // 如果有数据
            client.postMessage( { api:"getUserPassbyUrl", "user": user, "pass": pass }, ()=> {})
        }
    }

    client.onDisconnect.addListener(function() {
        if (pd_data()) {
            console.log(variable);
            localStorage.setItem(variable.url, JSON.stringify(variable));
        }
        //localStorage.setItem();
    });

    client.onMessage.addListener(function(msg) {
        switch(msg.api) {
            // 用户名提交api
            case "user":
                variable.user = msg.user;
                break;

            // 密码提交api
            case "pass":
                variable.pass = msg.pass;
                break;   
        }
    });

    function saveUrl() {
        variable.url = client.sender.origin;
    }

    // 判断数据是否有效
    function pd_data() {
        if (
            typeof variable.url != "undefined" &&
            typeof variable.user != "undefined" && 
            typeof variable.pass != "undefined"
            ) {
                return true;
            }
        return false;
    }

    function log(...msg) {
        console.log(...msg);
    }
});