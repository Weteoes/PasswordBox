<template>
  <div id="app">
    <router-view />
  </div>
</template>

<script>
export default {
  methods: {
    ready () {
      this.$store.state.weteoes = this.readyWeteoes()
    },
    readyWeteoes () {
      let w = window
      if (typeof w.weteoes === 'undefined') {
        w.weteoes = {}
      }
      // 设置w为Weteoes变量
      w = w.weteoes
      // 添加通用函数
      w.basic = {
        // 获取URL Get参数
        getQueryString: name => {
          const reg = new RegExp('(^|&)' + name + '=([^&]*)(&|$)')
          const r = window.location.search.substr(1).match(reg)
          if (r != null) return unescape(decodeURI(r[2]))
          return null
        },
        // Ajax
        ajax: (url, method, data) => {
          if (data === '' || data === undefined) {
            data = {}
          }
          const result = new Promise((resolve, reject) => {
            this.$axios({
              headers: {
                'Content-Type': 'application/x-www-form-urlencoded;charset=UTF-8'
              }, // 不发送options请求
              method: method,
              url: url,
              data: data,
              // 格式化data
              transformRequest: [
                function (data) {
                  let ret = ''
                  for (const it in data) {
                    ret += encodeURIComponent(it) + '=' + encodeURIComponent(data[it]) + '&'
                  }
                  return ret
                }
              ]
            }).then((r) => {
              this.debugLog(r)
              resolve(r)
            }).catch((e) => {
              this.debugLog(e)
              reject(e)
            })
          })
          return result
        },
        // Cookie
        cookie: {
          get (name) {
            const arr = document.cookie.match(
              new RegExp('(^| )' + name + '=([^;]*)(;|$)')
            )
            if (arr != null) return unescape(arr[2])
            return null
          },
          del (name) {
            const exp = new Date()
            exp.setTime(exp.getTime() - 1)
            const cval = w.basic.cookie.get(name)
            if (cval != null) {
              document.cookie =
              name + '=' + cval + ';expires=' + exp.toGMTString() + ';path=/'
            }
          }
        }
      }

      // String.format
      /// "{a}".format({a:1})
      String.prototype.format = function (args) {
        let result = this.substr()
        if (arguments.length > 0) {
          if (arguments.length === 1 && typeof args === 'object') {
            for (const key in args) {
              if (args[key] !== undefined) {
                const reg1 = new RegExp('({' + key + '})', 'g')
                result = result.replace(reg1, args[key])
              }
            }
          }
        }
        return result
      }
      // String.format End
      // Date.format
      /// new Date().format("yyyy-MM-dd HH:mm:ss");
      Date.prototype.format = function (fmt) {
        const o = {
          'M+': this.getMonth() + 1, // 月份
          'd+': this.getDate(), // 日
          'H+': this.getHours(), // 小时
          'm+': this.getMinutes(), // 分
          's+': this.getSeconds(), // 秒
          'q+': Math.floor((this.getMonth() + 3) / 3), // 季度
          S: this.getMilliseconds() // 毫秒
        }
        if (/(y+)/.test(fmt)) {
          fmt = fmt.replace(
            RegExp.$1,
            (this.getFullYear() + '').substr(4 - RegExp.$1.length)
          )
        }
        for (const k in o) {
          if (new RegExp('(' + k + ')').test(fmt)) {
            fmt = fmt.replace(
              RegExp.$1,
              RegExp.$1.length === 1
                ? o[k]
                : ('00' + o[k]).substr(('' + o[k]).length)
            )
          }
        }
        return fmt
      }
      // Date.format End
      return w
    },
    debugLog (...msg) {
      if (this.$store.state.debug) {
        window.console.log(...msg)
      }
    },
    log (...msg) {
      window.console.log(...msg)
    }
  },
  created () {
    this.ready()
  }
}
</script>
