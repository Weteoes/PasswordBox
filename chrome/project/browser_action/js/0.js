let app = new Vue({
    el: "#app",
    data() {
        return {
            console_options: [
                { 
                    name: "bilibili", title: "BiliBili 播放设置", options: [
                        { key: "bilibili_options_on", type:"switch", title: "全局开关", status: true },
                        { key: "bilibili_options_autoWidescreen", type:"switch", title: "自动打开宽屏", status: true },
                        { key: "bilibili_options_autoPlay", type:"switch", title: "自动播放", status: true },
                        { key: "bilibili_options_autoPlayContinue", type:"switch", title: "自动继续播放", status: true },
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
            // 如果找不到就是调试，不保存到chrome storage
            if (typeof chrome.storage == "undefined") { return; }
            chrome.storage.sync.set(obj, function(){
                console.log('保存成功！');
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
                            // 有数据
                            a = a == "true" ? true : false;
                            options_only.status = a;
                        } else  {
                            // 没数据，保存一份
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