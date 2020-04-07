addDocumentEvent();
// 保存全局变量
let variable = {
    RunTimeConnect: null, // socket长连接
}; 
function log(...msg) {
    console.log(...msg);
}
function main() {
    // 已经连接了一次就说明执行过了
    if (variable.RunTimeConnect != null) { return; }
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
    // 连接background
    socketConnect();
    // 添加事件
    addInputEvent(userInput, passInput);
    //log (userInput, passInput);
}

function socketConnect() {
    variable.RunTimeConnect = chrome.runtime.connect();
    variable.RunTimeConnect.onMessage.addListener(function(msg) {
        switch(msg.api) {
            // 判断是否有保存账户的网站
            case "getUserPassbyUrl":
                variable.input.userInput.value = msg.user;
                variable.input.passInput.value = msg.pass;
                break;
        }
    });
}

function addDocumentEvent() {
    document.onclick = main;
}

function addInputEvent(userInput, passInput) {
    function PostMessageUser(user) {
        variable.RunTimeConnect.postMessage( { api:"user", "user": user }, ()=> {})
    }
    function PostMessagePass(pass) {
        variable.RunTimeConnect.postMessage( { api:"pass", "pass": pass }, ()=> {})
    }
    let user = userInput.value;
    let pass = passInput.value;
    if (user != "") {
        PostMessageUser(user);
    }
    if (pass != "") {
        PostMessagePass(pass);
    }
    userInput.onchange = () => {
        let user = userInput.value;
        if (user == "") { return; }
        PostMessageUser(user);
    }
    passInput.onchange = () => {
        let pass = passInput.value;
        if (pass == "") { return; }
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

function findUserInput(PassInput) {
    let userInputType = "input[type=text]";
    let a = document.querySelectorAll(userInputType);
    if (a.length > 1) {
        // 如果有2个input以上，包括2个
        let passInputParent = null;
        while(1) {
            if (passInputParent == null) {
                // 如果等于null，说明第一次寻找，等于passInput父级
                passInputParent = PassInput.parentNode;
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
    return null;
}