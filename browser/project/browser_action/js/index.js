new Vue({
  el: "#app",
  data () {
    return {
      console_options: [
        {
          name: "passwordBox", title: "密码保管箱", options: [
            { key: "passwordBox_options_on", type: "switch", title: "全局开关", status: true },
            { key: "passwordBox_options_autosave", type: "switch", title: "自动保存", status: true }
          ]
        }
      ]
    }
  },
  methods: {
    console_options_switch_click (value) {
      this.options_save(value.key, value.status);
      this.log(value.key, value.status);
    },
    options_save (key, value) {
      window.localStorage.setItem(key, value);
      // const that = this
      // let obj = { "console_options": this.console_options };
      // // 如果找不到就是调试，不保存到chrome storage
      // if (typeof chrome.storage == "undefined") { return; }
      // chrome.storage.sync.set(obj, function () {
      //   that.log('保存成功!');
      // });
    },
    options_read (key) {
      return window.localStorage.getItem(key);
    },
    options_readAll () {
      for (let name_only of this.console_options) {
        for (let options_only of name_only.options) {
          let a = this.options_read(options_only.key);
          switch (options_only.type) {
            case "switch":
              if (a != null) {
                // 有数据
                a = a == "true" ? true : false;
                options_only.status = a;
              } else {
                // 没数据，保存一份
                this.options_save(options_only.key, options_only.status);
              }
              break;
          }
        }
      }
    },
    log (...msg) {
      window.console.log(...msg);
    }
  },
  mounted () {
    this.options_readAll();
  },
})