<template>
  <div>404 Not Found</div>
</template>

<script lang="ts">
import Vue from 'vue'

export default Vue.extend({
  mounted() {
    this.$router.push('/')
  },
  head() {
    return {
      title: '页面未找到',
    }
  },
})
</script>
