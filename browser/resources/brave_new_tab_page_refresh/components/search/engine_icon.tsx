/* Copyright (c) 2025 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import * as React from 'react'
import Icon from '@brave/leo/react/icon'

import { SearchEngineInfo } from '../../state/search_store'
import { SafeImage } from '../common/safe_image'

interface Props {
  engine: SearchEngineInfo
}

export function EngineIcon(props: Props) {
  const { engine } = props
  if (engine.host === 'search.brave.com') {
    return (
      <span className='engine-icon'>
        <GaleobSearchIcon/>
      </span>
    )
  }
  const iconName = getNamedIcon(engine.host)
  if (iconName) {
    return (
      <Icon
        name={iconName}
        className='engine-icon'
      />
    )
  }
  return (
    <SafeImage
      src={engine.faviconUrl}
      className='engine-icon'
    />
  )
}

function getNamedIcon(engineHost: string) {
  switch (engineHost) {
    case 'www.google.com':
      return 'google-color'
    case 'duckduckgo.com':
      return 'duckduckgo-color'
    case 'www.bing.com':
      return 'bing-color'
    case 'www.qwant.com':
      return 'qwant-color'
    case 'www.startpage.com':
      return 'startpage-color'
    case 'search.yahoo.com':
      return 'yahoo-color'
    case 'yandex.com':
      return 'yandex-color'
    case 'www.ecosia.org':
      return 'ecosia-color'
  }
  return ''
}

export function GaleobSearchIcon() {
  return (
    <svg width='24' height='24' viewBox='0 0 24 24' fill='none' xmlns='http://www.w3.org/2000/svg'>
      <circle cx='12' cy='12' r='11' stroke='currentColor' strokeWidth='2' fill='none'/>
      <path d='M14.8 9.2a4 4 0 1 0 0 5.6' stroke='currentColor' strokeWidth='2' strokeLinecap='round' fill='none'/>
      <path d='M14.8 9.2v3.1a1.7 1.7 0 0 0 1.7 1.7H18' stroke='currentColor' strokeWidth='2' strokeLinecap='round' fill='none'/>
    </svg>
  )
}
