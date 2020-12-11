import Vue from 'vue'

const common = {
  /**
   * 获取URL Get参数
   * @param variable 参数名
   */
  getQueryVariable(variable) {
    const query = window.location.search.substring(1)
    const vars = query.split('&')
    for (let i = 0; i < vars.length; i++) {
      const pair = vars[i].split('=')
      if (pair[0] === variable) {
        return pair[1]
      }
    }
    return false
  },
}
Vue.prototype.$common = common
