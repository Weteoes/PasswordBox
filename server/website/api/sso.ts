import request from '@/plugins/request'

export function getInfo () {
  return request({
    method: 'post',
    url: '/sso/login'
  })
}
