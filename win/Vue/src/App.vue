<template>
  <div>
    <router-view />
  </div>
</template>

<style>
* {
  margin: 0;
  padding: 0;
}
</style>

<script>
export default {
  methods: {
    ready: function () {
      let w = window
      if (typeof w.weteoes === 'undefined') {
        w.weteoes = {}
      }
      // 设置w为Weteoes变量
      w = w.weteoes
      // 添加通用函数
      w.basic = {}
      const basic = w.basic

      // 获取URL Get参数
      basic.getQueryString = name => {
        var reg = new RegExp('(^|&)' + name + '=([^&]*)(&|$)')
        var r = window.location.search.substr(1).match(reg)
        if (r != null) return unescape(decodeURI(r[2]))
        return null
      }
      // 获取URL Get参数  End
      // Ajax
      basic.ajax = (url, data, success, error) => {
        if (data === '' || data === undefined) {
          data = {}
        }
        if (typeof success !== 'function') {
          success = function () {}
        }
        if (typeof error !== 'function') {
          error = function () {}
        }
        this.$axios({
          headers: {
            'Content-Type': 'application/x-www-form-urlencoded;charset=UTF-8'
          }, // 不发送options请求
          method: 'post',
          url: url,
          data: data,
          // 格式化data
          transformRequest: [
            function (data) {
              let ret = ''
              for (const it in data) {
                ret +=
                  encodeURIComponent(it) +
                  '=' +
                  encodeURIComponent(data[it]) +
                  '&'
              }
              return ret
            }
          ]
          // 格式化data End
        })
          .then(success)
          .catch(error)
      }
      // Ajax End
      // Cookie
      basic.cookie = {
        get (name) {
          const arr = document.cookie.match(
            new RegExp('(^| )' + name + '=([^;]*)(;|$)')
          )
          if (arr != null) return unescape(arr[2])
          return null
        },
        del (name) {
          var exp = new Date()
          exp.setTime(exp.getTime() - 1)
          var cval = basic.cookie.get(name)
          if (cval != null) {
            document.cookie =
              name + '=' + cval + ';expires=' + exp.toGMTString() + ';path=/'
          }
        }
      }
      // cookie End
      // String.format
      /// / "{a}".format({a:1})
      String.prototype.format = function (args) {
        var result = this
        if (arguments.length > 0) {
          if (arguments.length === 1 && typeof args === 'object') {
            for (var key in args) {
              if (args[key] !== undefined) {
                var reg1 = new RegExp('({' + key + '})', 'g')
                result = result.replace(reg1, args[key])
              }
            }
          } else {
            for (var i = 0; i < arguments.length; i++) {
              if (arguments[i] !== undefined) {
                var reg2 = new RegExp('({)' + i + '(})', 'g')
                result = result.replace(reg2, arguments[i])
              }
            }
          }
        }
        return result
      }
      // String.format End
      // Date.format
      /// / new Date().format("yyyy-MM-dd HH:mm:ss");
      Date.prototype.format = function (fmt) {
        var o = {
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
        for (var k in o) {
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
    }
  },
  created () {
    this.ready()
  }
}
</script>
