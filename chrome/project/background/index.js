chrome.runtime.onConnect.addListener(function (client) {
    // ȫ�ֱ���
    let variable = {};
    // �������URL
    saveUrl();
    log(variable.url, "connect");
    // ��ȡ�˻���Ϣ
    getUserPassbyUrl();

    function getUserPassbyUrl() {
        let a = localStorage.getItem(variable.url);
        if (a == null) { return; }
        a = JSON.parse(a);
        let user = a.user, pass = a.pass;
        if (user != undefined && pass != undefined) {
            // ���������
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
            // �û����ύapi
            case "user":
                variable.user = msg.user;
                break;

            // �����ύapi
            case "pass":
                variable.pass = msg.pass;
                break;   
        }
    });

    function saveUrl() {
        let url;
        if (typeof client.sender.origin != "undefined") {
            // �����origin�˻�ʹ��
            url = client.sender.origin;
        } else {
            // ���������û��origin��Ҫ�Լ�����
            let a = client.sender.url;
            let b = a.indexOf("?");
            if (b != -1) {
                a = a.substr(0, b);
            } else {
                a = a.substr(0);
            }
            url = a;
        }
        variable.url = url;
    }

    // �ж������Ƿ���Ч
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