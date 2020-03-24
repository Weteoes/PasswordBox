let app = new Vue({
    el: "#app",
    data() {
        return {
            console_options: [
                { 
                    name: "bilibili", title: "BiliBili ��������", options: [
                        { key: "bilibili_options_on", type:"switch", title: "ȫ�ֿ���", status: true },
                        { key: "bilibili_options_autoWidescreen", type:"switch", title: "�Զ��򿪿���", status: true },
                        { key: "bilibili_options_autoPlay", type:"switch", title: "�Զ�����", status: true },
                        { key: "bilibili_options_autoPlayContinue", type:"switch", title: "�Զ���������", status: true },
                    ]
                }
            ],
            
        }
    },
    methods: {
        console_options_switch_click(value) {
            this.options_save(value.key, value.status);
        },
        options_save(key ,value) {
            window.localStorage.setItem(key, value);
            let obj = { "console_options": this.console_options };
            // ����Ҳ������ǵ��ԣ������浽chrome storage
            if (typeof chrome.storage == "undefined") { return; }
            chrome.storage.sync.set(obj, function(){
                console.log('����ɹ���');
            });
        },
        options_read(key) {
            return window.localStorage.getItem(key);
        },
        options_readAll() {
            for (let name_only of this.console_options) {
                for (let options_only of name_only.options) {
                    let a = this.options_read(options_only.key);
                    switch(options_only.type) {
                        case "switch": 
                        if (a != null) {
                            // ������
                            a = a == "true" ? true : false;
                            options_only.status = a;
                        } else  {
                            // û���ݣ�����һ��
                            this.options_save(options_only.key, options_only.status);
                        }
                        break;
                    }
                }
            }
        },
    },
    mounted() {
        this.options_readAll();
    },
})